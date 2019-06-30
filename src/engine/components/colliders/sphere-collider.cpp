#include "sphere-collider.hpp"

#include <engine/core/entity.hpp>
#include <engine/components/transform.hpp>

#include <stdexcept>
#include <iostream>

SphereCollider::SphereCollider(const float diameter)
    : diameter(diameter)
    , radius(diameter / 2.f)
    { }

void SphereCollider::Collide(Collider& collider) {
    collider.CollideWith(*this);
}

void SphereCollider::CollideWith(SphereCollider& sphere) {
    Entity* const owner = GetEntity();
    if (!owner) {
        throw new std::runtime_error("cannot check collision: no entity owning collider");
    }

    Transform& owner_transform = *owner->GetComponent<Transform>();
    Transform& other_transform = *sphere.GetEntity()->GetComponent<Transform>();

    if (owner_transform.DistanceTo(other_transform) > radius + sphere.radius) {
        return; // no collision
    }

    color = glm::vec3(0, 1, 0);
    sphere.color = glm::vec3(0, 1, 0);
}

glm::vec3 SphereCollider::Min(const Transform& transform) const {
    return transform.GetPosition() + glm::vec3(-radius);
}

glm::vec3 SphereCollider::Max(const Transform& transform) const {
    return transform.GetPosition() * glm::vec3(radius);
}
