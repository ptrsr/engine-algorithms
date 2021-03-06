#include "transform.hpp"

Transform::Transform(Entity* const entity, const glm::mat4& init_mat) 
    : Component(entity)
    , glm::mat4(init_mat)
    , transform(*this) 
    { }

glm::vec3 Transform::GetPosition() const {
    return glm::vec3(transform[3]);
}

Transform& Transform::SetPosition(const glm::vec3& position) {
    transform[3] = glm::vec4(position, 1);
    return *this;
}

Transform& Transform::Translate(const glm::vec3& translation) {
    transform[3] += glm::vec4(translation, 0);
    return *this;
}

Transform& Transform::Rotate(const float angle, const glm::vec3& axis) {
    transform = glm::rotate(transform, angle, axis);
    return *this;
}

Transform& Transform::Scale(const glm::vec3& scalar) {
    transform = glm::scale(transform, scalar);
    return *this;
}

Component_ptr Transform::Clone(Entity* const entity) {
    return Copy<Transform>(entity, *this);
}

float Transform::DistanceTo(const Transform& other) const {
    glm::distance(GetPosition(), other.GetPosition());
}


// void Transform::Remove(bool recursive) {
//     if (!parent && !recursive) {
//         throw std::runtime_error("Cannot remove without recursion: no parent to reattach children to");
//     }
//     if (recursive) {
//         // recurse over children
//         for (auto it = children.rbegin(); it != children.rend(); ++it) {
//             (*it)->Remove(true);
//         }
//         // after removing all children, remove this from parent
//         children.clear();
//         parent = nullptr;
//     } else {
//         // get temporary reference to avoid extra searching afterwards
//         Transform_ptr tmp_parent = parent;
//         if (tmp_parent) {
//             UnParent();
//         }
//         // move children to parent
//         for (auto it = children.rbegin(); it != children.rend(); ++it) {
//             Transform_ptr child = *it;
//             // manually set parent to nullptr to prevent search during AddChild step
//             child->parent = nullptr;

//             if (tmp_parent) {
//                 // add child to parent
//                 tmp_parent->AddChild(child);
//             }
//         }
//         children.clear();
//     }
// }

// Transform* Transform::RawClone() const {
//     return new Transform(*this);
// }

// Transform_ptr Transform::Clone(const bool recursive) const {
//     Transform_ptr clone = Transform_ptr(RawClone());
//     clone->parent = nullptr;
//     clone->children.clear();
    
//     if (!recursive) {
//         return clone;
//     }
//     for (auto it = children.begin(); it != children.end(); ++it) {
//         Transform_ptr clonedChild = (*it)->Clone(true);
//         clone->AddChild(clonedChild);
//     }
//     return clone;
// }
