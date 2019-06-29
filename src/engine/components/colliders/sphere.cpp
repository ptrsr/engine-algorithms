#include "sphere.hpp"

#include <engine/core/entity.hpp>
#include <engine/components/transform.hpp>

#include <stdexcept>
#include <iostream>

Sphere::Sphere(const float diameter)
    : diameter(diameter)
    , radius(diameter / 2.f)
    { }

void Sphere::Collide(Collider& collider) {
    std::cout << "error!" << std::endl;
}

void Sphere::CollideWith(Sphere& sphere) {
    Entity* const owner = GetEntity();
    if (!owner) {
        throw new std::runtime_error("cannot check collision: no entity owning collider");
    }

    Transform& owner_transform = *owner->GetComponent<Transform>();
    Transform& other_transform = *sphere.GetEntity()->GetComponent<Transform>();

    if (owner_transform.DistanceTo(other_transform) > radius + sphere.radius) {
        return; // no collision
    }

    std::cout << "boink!" << std::endl;
}

glm::vec3 Sphere::Min() {
    return glm::vec3(-radius);
}

glm::vec3 Sphere::Max() {
    return glm::vec3(radius);
}
