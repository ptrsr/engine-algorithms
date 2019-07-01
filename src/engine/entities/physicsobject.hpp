#ifndef PHYSICS_OBJECT_HPP_
#define PHYSICS_OBJECT_HPP_

#include <engine/entities/collisionobject.hpp>
#include <engine/components/physics.hpp>

class PhysicsObject : public CollisionObject {
public:
    Physics& physics;

    PhysicsObject(const unsigned id, std::unique_ptr<SphereCollider>&& collider, MeshMaterial_ptr& material, Mesh_ptr& mesh)
        : CollisionObject(id, std::move(collider), material, mesh)
        , physics(AddComponent<Physics>())
        { }

    PhysicsObject(const unsigned id, std::unique_ptr<AllignedBoxCollider>&& collider, MeshMaterial_ptr& material, Mesh_ptr& mesh)
        : CollisionObject(id, std::move(collider), material, mesh)
        , physics(AddComponent<Physics>())
        { }
};

#endif//PHYSICS_OBJECT_HPP_
