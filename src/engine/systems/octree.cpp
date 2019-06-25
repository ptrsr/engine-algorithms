#include "octree.hpp"

#include <engine/glm.hpp>

#include <engine/input/options.hpp>
#include <engine/input/file.hpp>
#include <engine/input/model.hpp>

#include <engine/components/mesh.hpp>
#include <engine/components/material.hpp>

#include <engine/entities/renderobject.hpp>


void Divide(OcNode& node) {
    node.nodes.reserve(8);

    for (unsigned i = 0; i < 8; ++i) {
        node.nodes.push_back(OcNode());
    }
}

OcTree::OcTree(const RenderObject& cube)
    : cube(cube)
    , parent_node(OcNode())
{
    Divide(parent_node);

    for (unsigned i = 0; i < 8; ++i) {
        Divide(parent_node.nodes[i]);
    }
}

void OcTree::Update(UpdateContext& context) {
    
    //Render();
}

void OcTree::Render(const OcNode& node, const glm::mat4 transform) const {

    

    
    // if (node.children.size() == 0) {
    //     return;
    // }
    // // render children
    // for (unsigned i = 0; i < 8; ++i) {
    //     Render(node.nodes[i]);
    // }
}
