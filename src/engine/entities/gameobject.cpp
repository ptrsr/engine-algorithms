#include "gameobject.hpp"

#include <engine/components/hierarchy.hpp>
#include <engine/components/transform.hpp>

GameObject::GameObject(const unsigned id)
    : Entity(id)
    , hierarchy(AddComponent<Hierarchy>())
    , transform(AddComponent<Transform>())
    { }
