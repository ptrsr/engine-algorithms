#ifndef PROJECTION_HPP_
#define PROJECTION_HPP_

#include <engine/core/component.hpp>
#include <engine/glm.hpp>

struct ProjectionContext {
    ProjectionContext(const float fov, const glm::vec2 windowSize, const float near, const float far);

    const glm::vec2 windowSize;
    const float fov;
    
    const float near;
    const float far;
};

class Projection : public Component, public ProjectionContext {
public:
    Projection(const ProjectionContext& context, Entity* const entity = nullptr);
    
    const glm::mat4 perspective;
};

#endif // PROJECTION_HPP_
