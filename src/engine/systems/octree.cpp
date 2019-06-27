#include "octree.hpp"

#include <engine/core/scene.hpp>
#include <engine/glm.hpp>

#include <engine/input/options.hpp>
#include <engine/input/file.hpp>
#include <engine/input/model.hpp>

#include <engine/components/mesh.hpp>
#include <engine/components/materials/meshmaterial.hpp>
#include <engine/components/transform.hpp>

#include <engine/entities/renderobject.hpp>
#include <engine/entities/camera.hpp>

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

OcTree::OcTree(const RenderObject& cube)
    : cube(cube)
    , parent_node(OcNode())
{
    parent_node.Divide(3);
}

void OcTree::Update(UpdateContext& context) {
    Camera& camera = *context.scene.GetEntity<Camera>();
    camera.transform.Rotate(0.01f, glm::vec3(0, 1, 0));

    cube.material.Use();
    cube.material.Bind(cube.mesh);

    glUniform3fv(cube.material.color_uniform, 1, glm::value_ptr(glm::vec3(1, 0, 0)));

    glm::mat4 vp = camera.projection.GetPerspective() * camera.transform;
    Render(parent_node, vp);
    
    cube.material.UnBind();
}

void OcTree::Render(const OcNode& node, const glm::mat4 transform) const {
    Transform local;
    local.SetPosition(node.local_pos / 4.f);
    local.Scale(glm::vec3(0.5f));

    glm::mat4 mvp = transform * local;
    glUniformMatrix4fv(cube.material.mvp_uniform, 1, false, glm::value_ptr(mvp));
    glDrawArrays(GL_LINES, 0, cube.mesh.vertex_buffer.size);
    
    if (node.nodes.size() == 0) {
        return;
    }
    // render children
    for (unsigned i = 0; i < 8; ++i) {
        Render(node.nodes[i], mvp);
    }
}
