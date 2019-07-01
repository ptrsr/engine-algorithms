#ifndef COLLISION_OBJECT_HPP_
#define COLLISION_OBJECT_HPP_

#include <engine/entities/renderobject.hpp>

#include <engine/components/collider.hpp>
#include <engine/components/mesh.hpp>
#include <engine/components/materials/mesh-material.hpp>
#include <engine/components/color.hpp>

#include <engine/components/colliders/sphere-collider.hpp>
#include <engine/components/colliders/alligned-box-collider.hpp>


class SphereCollider;
class CubeCollider;

class CollisionObject : public RenderObject {
public:
    Collider& collider;
    ColorComponent& color;

    CollisionObject(const unsigned id, std::unique_ptr<SphereCollider>&& collider, MeshMaterial_ptr& material, Mesh_ptr& mesh) 
        : RenderObject(id, material, mesh)
        , collider(AddComponent(std::move(collider))) 
        , color(AddComponent<ColorComponent>())
        { }

    CollisionObject(const unsigned id, std::unique_ptr<AllignedBoxCollider>&& collider, MeshMaterial_ptr& material, Mesh_ptr& mesh) 
        : RenderObject(id, material, mesh)
        , collider(AddComponent(std::move(collider))) 
        , color(AddComponent<ColorComponent>())
        { }
};

#endif//COLLISION_OBJECT_HPP_
