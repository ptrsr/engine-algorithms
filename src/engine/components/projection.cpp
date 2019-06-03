#include "projection.hpp"

#include <stdexcept>

Projection::Projection(Entity* const entity, const ProjectionContext& context)
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
#ifdef DEBUG
    if (fov <= 0 || near <= 0 || near > far) {
        throw new std::invalid_argument("Projection parameters invalid.");
    }
#endif
}
