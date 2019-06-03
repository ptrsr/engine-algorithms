#ifndef RENDERABLE_HPP_
#define RENDERABLE_HPP_

#include <engine/core/entity.hpp>
#include <engine/components/hierarchy.hpp>
#include <engine/components/transform.hpp>


class Hierarchy;
class Transform;

class GameObject : public Entity {
public:
    GameObject(const unsigned int id)
        : Entity(id)
        , hierarchy(AddComponent<Hierarchy>())
        , transform(AddComponent<Transform>())
        { }

    Hierarchy& hierarchy;
    Transform& transform;
};

#endif//RENDERABLE_HPP_
