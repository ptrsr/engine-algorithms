#include "simulator.hpp"

#include <stdlib.h>

#include <engine/core/scene.hpp>

#include <engine/components/colliders/sphere.hpp>
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
        CollisionObject& static_object = scene.AddEntity<CollisionObject>(
            std::make_unique<Sphere>(0.1f),
            material,
            sphere
        );

        static_object.transform.Scale(glm::vec3(0.1f));
        static_object.transform.SetPosition(GetRandomVec(-1.f, 1.f));

        scene.RegisterEntity<RenderObject>(static_object);
    }

    // dynamic objects
    srand(dynamic_seed);
    for (unsigned i = 0; i < context.dynamic_objects; ++i) {
        PhysicsObject& dynamic_object = scene.AddEntity<PhysicsObject>(
            std::make_unique<Sphere>(0.1f),
            material,
            sphere
        );

        dynamic_object.transform.Scale(glm::vec3(0.1f));
        dynamic_object.transform.SetPosition(GetRandomVec(-1.f, 1.f));
        dynamic_object.physics.velocity = GetRandomVec(-.01f, .01f);

        scene.RegisterEntity<RenderObject>(dynamic_object);
    }
}

void Simulator::Update(UpdateContext& context) {
    std::vector<PhysicsObject*> physics_objects = context.scene.GetEntities<PhysicsObject>();

    for (PhysicsObject* object : physics_objects) {
        object->transform.Translate(object->physics.velocity);
    }
}
