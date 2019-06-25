#ifndef OCTREE_HPP_
#define OCTREE_HPP_

#include <engine/core/system.hpp>

#include <engine/entities/gameobject.hpp>

#include <engine/components/material.hpp>
#include <engine/components/mesh.hpp>

#include <vector>


class RenderObject;

struct OcNode {
    std::vector<OcNode> nodes;
    std::vector<GameObject> children;
};

class OcTree : public System {
public:
    const RenderObject& cube;
    
    OcTree(const RenderObject& cube);
    void Update(UpdateContext& context) override;

private:
    OcNode parent_node;

    void Render(const OcNode& node, const glm::mat4 transform) const;
};

#endif//OCTREE_HPP_
