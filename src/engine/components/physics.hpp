#ifndef PHYSICS_HPP_
#define PHYSICS_HPP_

#include <engine/core/component.hpp>

#include <engine/glm.hpp>

class Entity;

class Physics : public Component {
public:
    glm::vec3 velocity;
    glm::vec3 rotation;

    Physics(Entity* const entity, const glm::vec3 velocity = glm::vec3(0), const glm::vec3 rotation = glm::vec3(0))
        : Component(entity)
        , velocity(velocity)
        , rotation(rotation)
        { }
};

#endif//PHYSICS_HPP_
