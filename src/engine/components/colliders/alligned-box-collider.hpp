#ifndef CUBE_COLLIDER_HPP_
#define CUBE_COLLIDER_HPP_

#include <engine/components/collider.hpp>

#include <vector>


class AllignedBoxCollider : public Collider {
public:
    const float size;

    AllignedBoxCollider(const float size)
        : size(size)
        { }

    bool Collide(Collider& collider) override;

    glm::vec3 Min(const Transform& transform) const override;
    glm::vec3 Max(const Transform& transform) const override;

protected:
    bool CollidesWith(Collider& other) override { return false; }
    bool CollidesWith(AllignedBoxCollider& other) override;
    bool CollidesWith(SphereCollider& other) override;
};

#endif//CUBE_COLLIDER_HPP_
