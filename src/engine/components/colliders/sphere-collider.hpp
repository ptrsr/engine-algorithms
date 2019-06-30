#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include <engine/components/collider.hpp>
#include <iostream>

class Transform;

class SphereCollider : public Collider {
public:
    const float diameter;
    const float radius;

    SphereCollider(const float diameter);
    void Collide(Collider& collider) override;

    glm::vec3 Min(const Transform& transform) const override;
    glm::vec3 Max(const Transform& transform) const override;

protected:
    void CollideWith(Collider& other) override { }
    void CollideWith(SphereCollider& other) override;

};

#endif//SPHERE_HPP_
