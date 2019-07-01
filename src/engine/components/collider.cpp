#include "collider.hpp"

#include <engine/core/entity.hpp>

#include <engine/components/transform.hpp>
#include <engine/components/colliders/alligned-box-collider.hpp>
#include <engine/components/colliders/sphere-collider.hpp>

#include <cmath>

bool Collider::Collides(SphereCollider& sphere, AllignedBoxCollider& box) {
    Transform& sphere_transform = *sphere.GetEntity()->GetComponent<Transform>();
    Transform& box_transform    = *box.GetEntity()->GetComponent<Transform>();

    glm::vec3 box_min = box.Min(box_transform);
    glm::vec3 box_max = box.Max(box_transform);

    glm::vec3 sphere_pos = sphere_transform.GetPosition();

    float dist = 0;
    for(unsigned i = 0; i < 3; ++i) {
        if (sphere_pos[i] < box_min[i]) {
            dist += std::sqrt(sphere_pos[i] - box_min[i]);
        } 
        else if (sphere_pos[i] > box_max[i]) {
            dist += std::sqrt(sphere_pos[i] - box_max[i]);
        }
    }
    if (dist <= std::pow(sphere.radius, 2.f)) {
        return true;
    }
    return false;
}

