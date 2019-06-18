#include "projection.hpp"

#include <stdexcept>

Projection::Projection(Entity* const entity, const float fov, const glm::vec2& window_size, const float near, const float far)
    : Component(entity)
    , fov(fov)
    , window_size(window_size)
    , near(near)
    , far(far)
    , perspective(glm::perspective(fov, window_size.x / window_size.y, near, far)) 
{
#ifdef DEBUG
    if (fov <= 0 || near <= 0 || near > far) {
        throw new std::invalid_argument("Projection parameters invalid.");
    }
#endif
}

void Projection::Calc() {
    perspective = glm::perspective(fov, window_size.x / window_size.y, near, far);
}

glm::vec2 Projection::GetWindowSize() const {
    return window_size;
}

void Projection::SetWindowSize(const glm::vec2& window_size) {
    this->window_size = window_size;
    Calc();
}

float Projection::GetFov() const {
    return fov;
}

void Projection::SetFov(const float fov) {
    this->fov = fov;
    Calc();
}

float Projection::GetNear() const {
    return near;
}

void Projection::SetNear(const float near) {
    this->near = near;
    Calc();
}

float Projection::GetFar() const {
    return far;
}

void Projection::SetFar(const float far) {
    this->far = far;
    Calc();
}

const glm::mat4& Projection::GetPerspective() const {
    return perspective;
}