#include "projector.hpp"

#include <cassert>

Projector::Projector(const Projector::Context& context, Entity* const entity)
    : Component(entity)
    , context(context)
    , projection(glm::perspective(context.fov, context.windowSize.x / context.windowSize.y, context.near, context.far)) 
    { }

Projector::Context::Context(const float fov, const glm::vec2 windowSize, const float near, const float far)
    : windowSize(windowSize)
    , fov(fov)
    , near(near)
    , far(far)
{ 
    assert(fov > 0);
    assert(near > 0);
    assert(far > near);
}