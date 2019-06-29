#include "octree.hpp"

#include <engine/core/scene.hpp>
#include <engine/glm.hpp>

#include <engine/input/options.hpp>
#include <engine/input/file.hpp>
#include <engine/input/model.hpp>

#include <engine/components/mesh.hpp>
#include <engine/components/materials/meshmaterial.hpp>
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
    nodes.reserve(8);
    for (int x = -1; x <= 1; x += 2) {
        for (int y = -1; y <= 1; y += 2) {
            for (int z = -1; z <= 1; z += 2) {
                OcNode& node = nodes.emplace_back(OcNode(glm::vec3(x, y, z)));
                node.Divide(layers - 1);
            }
        }
    }
}

void OcNode::Render(const glm::mat4 mvp, const RenderObject& cube) const {
    glUniformMatrix4fv(cube.material.mvp_uniform, 1, false, glm::value_ptr(mvp));
    glDrawArrays(GL_LINES, 0, cube.mesh.vertex_buffer.size);
    
    // render children
    for (const OcNode& child : nodes) {
        Transform local;
        local.SetPosition(child.local_pos / 4.f);
        local.Scale(glm::vec3(0.5f));

        child.Render(mvp * local, cube);
    }
}

OcTree::OcTree(const RenderObject& cube)
    : cube(cube)
    , parent_node(OcNode())
{
    parent_node.Divide(3);
}

void OcTree::Update(UpdateContext& context) {
    std::vector<PhysicsObject*> physics_objects = context.scene.GetEntities<PhysicsObject>();

    


    // Camera& camera = *context.scene.GetEntity<Camera>();
    // camera.transform.Rotate(0.01f, glm::vec3(0, 1, 0));
    // Render(camera);
}

void OcTree::EnforceBounds(std::vector<PhysicsObject*> physics_objects, glm::vec3 min, glm::vec3 max) {
for (PhysicsObject* object : physics_objects) {
        // world minimum and maximum positions
        glm::vec3 w_max = object->transform.GetPosition() + object->collider.Max();
        glm::vec3 w_min = object->transform.GetPosition() + object->collider.Min();

        glm::vec3 normal = glm::vec3(0);
        glm::vec3 delta = glm::vec3(0);

        {
            glm::vec3 d_min = glm::min(w_min, min) - min;
            delta += d_min;
            normal += glm::floor(d_min);
        }
        {
            glm::vec3 d_max = glm::max(w_max, max) - max;
            delta += d_max;
            normal += glm::ceil(d_max);
        }

        if (normal == glm::vec3(0)) {
            // no bounce
            continue;
        }

        object->transform.Translate(-delta * 2.f);

        // ensure no consistent speed
        const float speed = glm::length(object->physics.velocity);
        object->physics.velocity = glm::normalize(glm::reflect(object->physics.velocity, normal)) * speed;
    }
}

void OcTree::Render(const Camera& camera) const {
    cube.material.Use();
    cube.material.Bind(cube.mesh);
    
    glUniform3fv(cube.material.color_uniform, 1, glm::value_ptr(glm::vec3(1, 0, 0)));

    glm::mat4 vp = camera.projection.GetPerspective() * camera.transform;
    parent_node.Render(vp, cube);

    cube.material.UnBind();
}
