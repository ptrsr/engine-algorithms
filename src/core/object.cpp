#include "object.hpp"
#include <iostream>
#include <exception>

Object::Object(const glm::mat4& transform) 
    : transform(transform) {

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

bool Object::AddChild(Object_ptr child) {
    child->parent = shared_from_this();
    children.push_back(child);
}

void Object::UnParent() {
    if (parent == nullptr) {
        throw std::runtime_error("cannot unparent: no parent");
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

const Object_ptr Object::GetParent() {
    return parent;
}

const std::vector<Object_ptr>& Object::GetChildren() {
    return children;
}

