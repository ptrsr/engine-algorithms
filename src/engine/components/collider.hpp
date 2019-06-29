#ifndef COLIDER_HPP_
#define COLIDER_HPP_

#include <engine/core/component.hpp>
#include <engine/glm.hpp>

class Sphere;

class Collider : public Component {
public:
    virtual void Collide(Collider& other) = 0;

    virtual glm::vec3 Min() = 0;
    virtual glm::vec3 Max() = 0;

protected:
    virtual void CollideWith(Collider& other) = 0;
    virtual void CollideWith(Sphere& other) = 0;
};

typedef std::shared_ptr<Collider> Collider_ptr;

#endif//COLIDER_HPP_
