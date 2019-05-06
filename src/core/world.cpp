#include <core/object.hpp>
#include "world.hpp"

Object_ptr World::CreateObject() {
    return std::make_shared<Object>(*this);
}

const std::vector<Object_ptr> World::GetChildren() const {
    return children;
}
