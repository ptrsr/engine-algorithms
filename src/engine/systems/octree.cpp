#include "octree.hpp"

#include <engine/core/scene.hpp>
#include <engine/glm.hpp>

#include <engine/input/options.hpp>
#include <engine/input/file.hpp>
#include <engine/input/model.hpp>

#include <engine/components/mesh.hpp>
#include <engine/components/materials/mesh-material.hpp>
#include <engine/components/transform.hpp>
#include <engine/components/collider.hpp>

#include <engine/entities/renderobject.hpp>
#include <engine/entities/camera.hpp>
#include <engine/entities/physicsobject.hpp>

#include <iostream>


void OcNode::Divide(const unsigned layers) {
    if (layers == 0) {
        return;
    }
    leaves.reserve(8);
    for (int x = -1; x <= 1; x += 2) {
        for (int y = -1; y <= 1; y += 2) {
            for (int z = -1; z <= 1; z += 2) {
                const float leaf_size = size / 2;
                glm::vec3 leaf_position = position + glm::vec3(x, y, z) * leaf_size / 2.f;

                OcNode& leaf = leaves.emplace_back(OcNode(this, leaf_size, leaf_position));
                leaf.Divide(layers - 1);
            }
        }
    }
}

void OcNode::Render(const glm::mat4 vp, const RenderObject& cube) const {
    Transform local;
    local.SetPosition(position);
    local.Scale(glm::vec3(size));

    const glm::mat4 mvp =  vp * local;
    
    glUniformMatrix4fv(cube.material.mvp_uniform, 1, false, glm::value_ptr(mvp));

    if (children.size() != 0) {
        glDrawArrays(GL_LINES, 0, cube.mesh.vertex_buffer.size);
    }
    
    // render children
    for (const OcNode& child : leaves) {
        child.Render(vp, cube);
    }
}

glm::vec3 OcNode::Fits(const CollisionObject& object) const {
        // object corners
        glm::vec3 o_max = object.collider.Max(object.transform);
        glm::vec3 o_min = object.collider.Min(object.transform);

        // node corners
        glm::vec3 n_max = position + glm::vec3(size) / 2.f;
        glm::vec3 n_min = position - glm::vec3(size) / 2.f;

        // outside vector (0 if completely inside)
        glm::vec3 delta = glm::vec3(0);
        delta += glm::min(o_min, n_min) - n_min;
        delta += glm::max(o_max, n_max) - n_max;
        return delta;
}

void OcNode::ResolveCollision(std::vector<CollisionObject*> objects = std::vector<CollisionObject*>()) {
    // for each of this node's children
    for (auto it = children.begin(); it < children.end(); ++it) {
        // node child
        CollisionObject* child = *it;

        // for each upper object
        for (CollisionObject* object : objects) {
            object->collider.Collide(child->collider);
        }
        // for each other child in this node
        for (auto n_it = it + 1; n_it < children.end(); ++n_it) {
            CollisionObject* other_child = *n_it;
            other_child->collider.Collide(child->collider);
        }
    }
    // resolve leaves
    std::vector<CollisionObject*> new_objects = objects;
    new_objects.insert(new_objects.end(), children.begin(), children.end());

    for (OcNode& leaf : leaves) {
        leaf.ResolveCollision(new_objects);
    }
}

bool OcNode::Place(CollisionObject& object) {
    glm::vec3 delta = Fits(object);

    if (delta != glm::vec3()) {
        return false;
    }

    bool fit = false;
    for (OcNode& leaf : leaves) {
        if (!leaf.Place(object)) {
            continue;
        }
        fit = true;
        break;
    }
    if (!fit) {
        children.push_back(&object);
    }
    return true;
}

OcTree::OcTree(const RenderObject& cube)
    : cube(cube)
    , parent_node(OcNode(nullptr, 1.f, glm::vec3()))
{
    parent_node.Divide(4);
}

void OcTree::Start(Scene& scene) {
    // place static objects
    std::vector<CollisionObject*> static_objects = scene.GetEntities<CollisionObject>();
    for (CollisionObject* object : static_objects) {
        if (parent_node.Place(*object)) {
            continue;
        }
        // place the object back in main cube
        glm::vec3 delta = parent_node.Fits(*object);
        object->transform.Translate(-delta * 2.f);

        parent_node.Place(*object);
    }
}

void OcTree::Update(UpdateContext& context) {
    std::vector<PhysicsObject*> physics_objects = context.scene.GetEntities<PhysicsObject>();

    OcNode node = parent_node;
    for (PhysicsObject* object : physics_objects) {
        if (node.Place(*object)) {
            continue;
        }
        // place the object back in main cube
        glm::vec3 delta = node.Fits(*object);
        object->transform.Translate(-delta * 2.f);

        // reflect and ensure consistent speed
        const float speed = glm::length(object->physics.velocity);
        object->physics.velocity = glm::normalize(glm::reflect(object->physics.velocity, glm::normalize(delta))) * speed;

        // place the object back now that it fits
        node.Place(*object);
    }

    node.ResolveCollision();

    // render
    Camera& camera = *context.scene.GetEntity<Camera>();
    camera.transform.Rotate(0.01f, glm::vec3(0, 1, 0));
    Render(camera, node);
}

void OcTree::Render(const Camera& camera, const OcNode& node) const {
    cube.material.Use();
    cube.material.Bind(cube.mesh);
    
    glUniform3fv(cube.material.color_uniform, 1, glm::value_ptr(glm::vec3(1, 0, 0)));

    glm::mat4 vp = camera.projection.GetPerspective() * camera.transform;
    node.Render(vp, cube);

    cube.material.UnBind();
}
