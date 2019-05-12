#include "transform.hpp"

Transform::Transform(glm::mat4 init_mat) 
    : glm::mat4(init_mat)
    , transform(*this) { }

glm::vec3 Transform::GetPosition() const {
    return glm::vec3(transform[3]);
}

void Transform::SetPosition(const glm::vec3& position) {
    transform[3] = glm::vec4(position, 1);
}

void Transform::Translate(const glm::vec3& translation) {
    transform[3] += glm::vec4(translation, 0);
}

void Transform::Rotate(const float angle, const glm::vec3& axis) {
    transform = glm::rotate(transform, angle, axis);
}

bool Transform::AddChild(const Transform_ptr& child) {
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

void Transform::UnParent() {
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

const Transform_ptr Transform::GetParent() const {
    return parent;
}

const std::vector<Transform_ptr>& Transform::GetChildren() const {
    return children;
}

void Transform::Remove(bool recursive) {
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
        Transform_ptr tmp_parent = parent;
        if (tmp_parent) {
            UnParent();
        }
        // move children to parent
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            Transform_ptr child = *it;
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

Transform* Transform::RawClone() const {
    return new Transform(*this);
}

Transform_ptr Transform::Clone(const bool recursive) const {
    Transform_ptr clone = Transform_ptr(RawClone());
    clone->parent = nullptr;
    clone->children.clear();
    
    if (!recursive) {
        return clone;
    }
    for (auto it = children.begin(); it != children.end(); ++it) {
        Transform_ptr clonedChild = (*it)->Clone(true);
        clone->AddChild(clonedChild);
    }
    return clone;
}

// void Transform::SendMessage(const Message& message) {
//     message.Execute(*this);
// }
