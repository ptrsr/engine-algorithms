#include "camera.hpp"

Camera::Camera(const float fov,
               const glm::vec2 windowSize,
               const float near, 
               const float far) {
    projection = glm::perspective(
        fov, 
        windowSize.x / windowSize.y,
        near,
        far);
}

const glm::mat4& Camera::GetProjection() const {
    return projection;
}
