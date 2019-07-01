#include "simulator.hpp"

#include <stdlib.h>

#include <engine/core/scene.hpp>

#include <engine/components/colliders/sphere-collider.hpp>
#include <engine/components/colliders/alligned-box-collider.hpp>

#include <engine/components/transform.hpp>

#include <engine/entities/physicsobject.hpp>

float GetRandom(const float min, const float max) {
    if (min > max) {
        throw new std::runtime_error("min is more than max");
    }
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(max-min)));
}

glm::vec3 GetRandomVec(const float min, const float max) {
    return glm::vec3(GetRandom(min, max), GetRandom(min, max), GetRandom(min, max));
}

void SetParameters(CollisionObject& static_object, const float scale, const float spawn_box_size) {
    static_object.transform.Scale(glm::vec3(scale));
    static_object.transform.SetPosition(GetRandomVec(-spawn_box_size, spawn_box_size));
}

void SetParameters(PhysicsObject& dynamic_object, const float scale, const float spawn_box_size, const float max_velocity) {
    dynamic_object.physics.velocity = GetRandomVec(-max_velocity, max_velocity);
    SetParameters(dynamic_object, scale, spawn_box_size);
}

Simulator::Simulator(Scene& scene, 
                     Mesh_ptr& cube, 
                     Mesh_ptr& sphere,
                     MeshMaterial_ptr& material, 
                     const SimulatorContext& context) 
{
    srand(context.seed);
    const int static_seed  = rand();
    const int dynamic_seed = rand();

    // static objects
    srand(static_seed);
    for (unsigned i = 0; i < context.static_objects; ++i) {
        {
            auto& static_object = Spawn<CollisionObject, SphereCollider>(scene, sphere, material, 0.05f);
            SetParameters(static_object, 0.05f, 1.f);
        }
        {
            auto& static_object = Spawn<CollisionObject, AllignedBoxCollider>(scene, cube, material, 0.1f);
            SetParameters(static_object, 0.1f, 1.f);
        }
    }

    // dynamic objects
    srand(dynamic_seed);
    for (unsigned i = 0; i < context.dynamic_objects; ++i) {
        {
            auto& dynamic_object = Spawn<PhysicsObject, SphereCollider>(scene, sphere, material, 0.05f);
            SetParameters(dynamic_object, 0.05f, 0.5f, 0.01f);
        }
        {
            auto& dynamic_object = Spawn<PhysicsObject, AllignedBoxCollider>(scene, cube, material, 0.1f);
            SetParameters(dynamic_object, 0.1f, 0.5f, 0.01f);
        }
    }
}

void Simulator::Update(UpdateContext& context) {
    std::vector<PhysicsObject*> physics_objects = context.scene.GetEntities<PhysicsObject>();

    for (PhysicsObject* object : physics_objects) {
        object->transform.Translate(object->physics.velocity);
    }
}
