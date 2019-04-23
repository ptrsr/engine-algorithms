#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <core/object.hpp>

class Camera : Object {
    public:
        Camera(const float fov,
               const glm::vec2 windowSize, 
               const float near, 
               const float far);

    const glm::mat4& GetProjection() const;

    private:
        glm::mat4 projection;
};

#endif // CAMERA_HPP_
