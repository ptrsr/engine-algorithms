#include "octree.hpp"

#include <engine/core/scene.hpp>
#include <engine/glm.hpp>

#include <engine/input/options.hpp>
#include <engine/input/file.hpp>
#include <engine/input/model.hpp>

#include <engine/components/materials/mesh-material.hpp>
#include <engine/components/transform.hpp>
#include <engine/components/collider.hpp>
#include <engine/components/mesh.hpp>
#include <engine/components/timer.hpp>

#include <engine/entities/renderobject.hpp>
#include <engine/entities/physicsobject.hpp>
#include <engine/entities/profiler.hpp>
#include <engine/entities/camera.hpp>


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

void OcNode::GetCollisions(Collisions& collisions, std::vector<CollisionObject*> objects = std::vector<CollisionObject*>()) {
    // for each of this node's children
    for (auto it = children.begin(); it < children.end(); ++it) {
        // node child
        CollisionObject* child = *it;

        // for each upper object
        for (CollisionObject* object : objects) {
            if (object->collider.Collide(child->collider)) {
                collisions.push_back(Collision(object, child));
            }
        }
        // for each other child in this node
        for (auto n_it = it + 1; n_it < children.end(); ++n_it) {
            CollisionObject* other_child = *n_it;
            if (child->collider.Collide(other_child->collider)) {
                collisions.push_back(Collision(child, other_child));
            }
        }
    }
    // resolve leaves
    std::vector<CollisionObject*> new_objects = objects;
    new_objects.insert(new_objects.end(), children.begin(), children.end());

    for (OcNode& leaf : leaves) {
        leaf.GetCollisions(collisions, new_objects);
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
    parent_node.Divide(3);
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
    //profiling
    Timer& timer = context.scene.GetEntity<Profiler>()->timer;
    auto octree_tracker = timer.Start("OcTree");
    auto collisions_tracker = timer.Start("Collisions");

    // copy the tree with static objects
    OcNode node = parent_node;
    std::vector<PhysicsObject*> dynamic_objects = context.scene.GetEntities<PhysicsObject>();

    // put all the dynamic objects in the tree
    for (PhysicsObject* object : dynamic_objects) {
        // NOTE: to be removed!
        object->color.color = glm::vec3(1, 0, 0);

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

    // NOTE: temporary!
    std::vector<CollisionObject*> static_objects = context.scene.GetEntities<CollisionObject>();
    for (CollisionObject* object : static_objects) {
        object->color.color = glm::vec3(1, 0, 0);
    }

    auto resolve_tracker = timer.Start("Resolving");

    // resolve collisions
    Collisions collisions;
    node.GetCollisions(collisions);
    for (Collision& collision : collisions) {
        OnCollision(*collision.first, *collision.second);
    }

    timer.Stop(resolve_tracker);
    timer.Stop(collisions_tracker);
    auto render_tracker = timer.Start("Render");

    // render
    Camera& camera = *context.scene.GetEntity<Camera>();
    camera.transform.Rotate(0.01f, glm::vec3(0, 1, 0));
    Render(camera, node);

    timer.Stop(render_tracker);
    timer.Stop(octree_tracker);
}

void OcTree::OnCollision(CollisionObject& a, CollisionObject& b) {
    a.color.color = glm::vec3(0, 1, 0);
    b.color.color = glm::vec3(0, 1, 0);
}


void OcTree::Render(const Camera& camera, const OcNode& node) const {
    cube.material.Use();
    cube.material.Bind(cube.mesh);
    
    glUniform3fv(cube.material.color_uniform, 1, glm::value_ptr(glm::vec3(1, 0, 0)));

    glm::mat4 vp = camera.projection.GetPerspective() * camera.transform;
    node.Render(vp, cube);

    cube.material.UnBind();
}
