#ifndef COLIDER_HPP_
#define COLIDER_HPP_

#include <engine/core/component.hpp>
#include <engine/glm.hpp>

class Transform;
class SphereCollider;
class AllignedBoxCollider;

class Collider : public Component {
public:
    virtual bool Collide(Collider& other) = 0;

    virtual glm::vec3 Min(const Transform& transform) const = 0;
    virtual glm::vec3 Max(const Transform& transform) const = 0;

    virtual bool CollidesWith(Collider& other) = 0;
    virtual bool CollidesWith(SphereCollider& other) = 0;
    virtual bool CollidesWith(AllignedBoxCollider& other) = 0;

    bool Collides(SphereCollider& sphere, AllignedBoxCollider& box);
};

typedef std::shared_ptr<Collider> Collider_ptr;

#endif//COLIDER_HPP_
