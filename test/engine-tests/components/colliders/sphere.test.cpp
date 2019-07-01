#include <gtest/gtest.h>

#include <engine/components/colliders/sphere-collider.hpp>

#include <engine/components/materials/mesh-material.hpp>
#include <engine/components/mesh.hpp>

#include <engine/entities/collisionobject.hpp>

#include <iostream>

TEST(CollisionObject, lmao) {
    auto material = std::make_shared<MeshMaterial>(std::string(TEST_RESOURCE_DIR) + "cube");
    auto mesh = std::make_shared<Mesh>(std::string(TEST_RESOURCE_DIR) + "cube");

    CollisionObject obj = CollisionObject(
        0,
        std::make_unique<SphereCollider>(1.f),
        material, 
        mesh
    );
}
