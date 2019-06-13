#ifndef RENDERABLE_HPP_
#define RENDERABLE_HPP_

#include <engine/core/entity.hpp>

class Hierarchy;
class Transform;

class GameObject : public Entity {
public:
    GameObject(const unsigned int id);

    Hierarchy& hierarchy;
    Transform& transform;
};

#endif//RENDERABLE_HPP_
