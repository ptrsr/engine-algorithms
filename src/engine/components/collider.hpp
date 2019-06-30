#ifndef COLIDER_HPP_
#define COLIDER_HPP_

#include <engine/core/component.hpp>
#include <engine/glm.hpp>

class Transform;
class SphereCollider;

class Collider : public Component {
public:
    virtual void Collide(Collider& other) = 0;

    virtual glm::vec3 Min(const Transform& transform) const = 0;
    virtual glm::vec3 Max(const Transform& transform) const = 0;

    virtual void CollideWith(Collider& other) = 0;
    virtual void CollideWith(SphereCollider& other) = 0;

    glm::vec3 color = glm::vec3(1, 0, 1);
};

typedef std::shared_ptr<Collider> Collider_ptr;

#endif//COLIDER_HPP_
