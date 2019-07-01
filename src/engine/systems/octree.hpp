#ifndef OCTREE_HPP_
#define OCTREE_HPP_

#include <engine/core/system.hpp>

#include <engine/entities/gameobject.hpp>

#include <engine/components/material.hpp>
#include <engine/components/mesh.hpp>

#include <vector>


class PhysicsObject;
class RenderObject;
class CollisionObject;
class Camera;

typedef std::pair<CollisionObject*, CollisionObject*> Collision;
typedef std::vector<Collision> Collisions;

struct OcNode {

    const OcNode* parent;
    const float size;
    const glm::vec3 position;

    std::vector<OcNode> leaves;
    std::vector<CollisionObject*> children;

    OcNode(const OcNode* parent, const float size, const glm::vec3& position)
        : parent(parent)
        , size(size)
        , position(position)
        { }

    OcNode(const OcNode& original) = default;

    void Divide(const unsigned layers = 1);
    void Render(const glm::mat4 mvp, const RenderObject& cube) const;
    glm::vec3 Fits(const CollisionObject& object) const;
    bool Place(CollisionObject& object);
    void GetCollisions(Collisions& collisions, std::vector<CollisionObject*> objects);

};

class OcTree : public System {
public:
    OcNode parent_node;
    const RenderObject& cube;
    
    OcTree(const RenderObject& cube);
    void Start(Scene& scene) override;
    void Update(UpdateContext& context) override;

    virtual void OnCollision(CollisionObject& a, CollisionObject& b);

private:
    void Render(const Camera& camera, const OcNode& node) const;
};

#endif//OCTREE_HPP_
