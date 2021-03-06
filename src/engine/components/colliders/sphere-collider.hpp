#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include <engine/components/collider.hpp>
#include <iostream>

class Transform;
class AllignedBoxCollider;

class SphereCollider : public Collider {
public:
    const float radius;

    SphereCollider(const float radius);
    bool Collide(Collider& collider) override;

    glm::vec3 Min(const Transform& transform) const override;
    glm::vec3 Max(const Transform& transform) const override;

protected:
    bool CollidesWith(Collider& other) override { return false; }
    bool CollidesWith(SphereCollider& other) override;
    bool CollidesWith(AllignedBoxCollider& other) override;

};

#endif//SPHERE_HPP_
