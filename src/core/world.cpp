#include "world.hpp"
#include <core/object.hpp>

Object_ptr World::CreateObject() {
    Object_ptr object = std::make_shared<Object>(*this);
}

const std::vector<Object_ptr> World::GetChildren() const {
    return children;
}
