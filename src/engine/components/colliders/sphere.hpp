#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include <engine/components/collider.hpp>
#include <iostream>

class Transform;

class Sphere : public Collider {
public:
    const float diameter;
    const float radius;

    Sphere(const float diameter);
    void Collide(Collider& collider) override;

    glm::vec3 Min() override;
    glm::vec3 Max() override;

protected:
    void CollideWith(Collider& other) override { }
    void CollideWith(Sphere& other) override;

};

#endif//SPHERE_HPP_
