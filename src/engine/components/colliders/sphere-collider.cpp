#include "sphere-collider.hpp"
#include "alligned-box-collider.hpp"

#include <engine/core/entity.hpp>
#include <engine/components/transform.hpp>

#include <stdexcept>
#include <iostream>

SphereCollider::SphereCollider(const float radius)
    : radius(radius)
    { }

glm::vec3 SphereCollider::Min(const Transform& transform) const {
    return transform.GetPosition() + glm::vec3(-radius);
}

glm::vec3 SphereCollider::Max(const Transform& transform) const {
    return transform.GetPosition() + glm::vec3(radius);
}

bool SphereCollider::Collide(Collider& collider) {
    return collider.CollidesWith(*this);
}

bool SphereCollider::CollidesWith(SphereCollider& other) {
    Entity* const owner = GetEntity();
    if (!owner) {
        throw new std::runtime_error("cannot check collision: no entity owning collider");
    }

    Transform& owner_transform = *owner->GetComponent<Transform>();
    Transform& other_transform = *other.GetEntity()->GetComponent<Transform>();

    if (owner_transform.DistanceTo(other_transform) > radius + other.radius) {
        return false; // no collision
    }
    return true;
}

bool SphereCollider::CollidesWith(AllignedBoxCollider& other) {
    return Collides(*this, other);
}

