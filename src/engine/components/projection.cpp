#include "projection.hpp"

#include <cassert>

Projection::Projection(const ProjectionContext& context, Entity* const entity)
    : Component(entity)
    , ProjectionContext(context)
    , perspective(glm::perspective(context.fov, context.windowSize.x / context.windowSize.y, context.near, context.far)) 
    { }

ProjectionContext::ProjectionContext(const float fov, const glm::vec2 windowSize, const float near, const float far)
    : windowSize(windowSize)
    , fov(fov)
    , near(near)
    , far(far)
{ 
    assert(fov > 0);
    assert(near > 0);
    assert(far > near);
}
