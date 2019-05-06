#include "object.hpp"

#include <iostream>
#include <exception>

Object::Object(World& world) 
    : world(world)
    , transform(glm::mat4(1)) {
    
}

const glm::mat4& Object::GetTransform() {
    return transform;
}

glm::vec3 Object::GetPosition() {
    return glm::vec3(transform[3]);
}

void Object::SetPosition(const glm::vec3& position) {
    transform[3] = glm::vec4(position, 1);
}

void Object::Translate(const glm::vec3& translation) {
    transform[3] += glm::vec4(translation, 0);
}

void Object::Rotate(const float angle, const glm::vec3& axis) {
    transform = glm::rotate(transform, angle, axis);
}

bool Object::AddChild(const Object_ptr& child) {
    if (child->parent != nullptr) {
        if (child->parent.get() == this) {
            throw std::runtime_error("Cannot add child: already childed to this object.");
        } else {
            // unparent if already attached
            child->UnParent();
        }
    }
    child->parent = shared_from_this();
    children.push_back(child);
}

void Object::UnParent() {
    if (parent == nullptr) {
        throw std::runtime_error("Cannot unparent: no parent.");
    }
    for (auto i = parent->children.begin(); i != parent->children.end(); ++i) {
        if ((*i).get() != this) {
            continue;
        }
        parent->children.erase(i);
        break;
    }
    parent = nullptr;
}

const Object_ptr Object::GetParent() const {
    return parent;
}

const std::vector<Object_ptr>& Object::GetChildren() const {
    return children;
}

void Object::Remove(bool recursive) {
    if (!parent && !recursive) {
        throw std::runtime_error("Cannot remove without recursion: no parent to reattach children to");
    }
    if (recursive) {
        // recurse over children
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            (*it)->Remove(true);
        }
        // after removing all children, remove this from parent
        children.clear();
        parent = nullptr;
    } else {
        // get temporary reference to avoid extra searching afterwards
        Object_ptr tmp_parent = parent;
        if (tmp_parent) {
            UnParent();
        }
        // move children to parent
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            Object_ptr child = *it;
            // manually set parent to nullptr to prevent search during AddChild step
            child->parent = nullptr;

            if (tmp_parent) {
                // add child to parent
                tmp_parent->AddChild(child);
            }
        }
        children.clear();
    }
}

Object* Object::RawClone() const {
    return new Object(*this);
}

Object_ptr Object::Clone(const bool recursive) const {
    Object_ptr clone = Object_ptr(RawClone());
    clone->parent = nullptr;
    clone->children.clear();
    
    if (!recursive) {
        return clone;
    }
    for (auto it = children.begin(); it != children.end(); ++it) {
        Object_ptr clonedChild = (*it)->Clone(true);
        clone->AddChild(clonedChild);
    }
    return clone;
}

// void Object::SendMessage(const Message& message) {
//     message.Execute(*this);
// }
