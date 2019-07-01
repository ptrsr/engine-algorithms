#include "alligned-box-collider.hpp"
#include "sphere-collider.hpp"

#include <engine/core/entity.hpp>
#include <engine/components/transform.hpp>


#include <iostream>

glm::vec3 AllignedBoxCollider::Max(const Transform& transform) const {
    return transform.GetPosition() + glm::vec3(size);
}

glm::vec3 AllignedBoxCollider::Min(const Transform& transform) const {
    return transform.GetPosition() - glm::vec3(size);
}

bool AllignedBoxCollider::Collide(Collider& collider) {
    return collider.CollidesWith(*this);
}

bool AllignedBoxCollider::CollidesWith(AllignedBoxCollider& other) {
    Transform& owner_transform = *GetEntity()->GetComponent<Transform>();
    Transform& other_transform = *other.GetEntity()->GetComponent<Transform>();

    glm::vec3 owner_min = Min(owner_transform);
    glm::vec3 owner_max = Max(owner_transform);

    glm::vec3 other_min = other.Min(other_transform);
    glm::vec3 other_max = other.Max(other_transform);

    // check for overlap in each axis
    for (unsigned i = 0; i < 3; ++i) {
        if (!(owner_min[i] <= other_max[i] && owner_max[i] >= other_min[i])) {
            // doesn't overlap
            return false;
        }
    }
    return true;
}

bool AllignedBoxCollider::CollidesWith(SphereCollider& other) {
    return Collides(other, *this);
}
