#ifndef OCTREE_HPP_
#define OCTREE_HPP_

#include <engine/core/system.hpp>

#include <engine/entities/gameobject.hpp>

#include <engine/components/material.hpp>
#include <engine/components/mesh.hpp>

#include <vector>


class RenderObject;
class Camera;

struct OcNode {
    std::vector<OcNode> nodes;
    std::vector<GameObject> children;
    glm::vec3 local_pos;

    OcNode(const glm::vec3& local_pos = glm::vec3(0, 0, 0))
        : local_pos(local_pos)
        { }

    void Divide(const unsigned layers = 1);
    void Render(const glm::mat4 mvp, const RenderObject& cube) const;
};

class OcTree : public System {
public:
    OcNode parent_node;
    const RenderObject& cube;
    
    OcTree(const RenderObject& cube);
    void Update(UpdateContext& context) override;

private:
    void Render(const Camera& camera) const;
};

#endif//OCTREE_HPP_
