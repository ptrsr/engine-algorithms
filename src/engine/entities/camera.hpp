#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <engine/entities/gameobject.hpp>
#include <engine/components/transform.hpp>
#include <engine/components/projection.hpp>

class Camera : public GameObject {
public:
    Camera(const unsigned id, const float fov, const glm::vec2& window_size, const float near, const float far)
        : GameObject(id)
        , projection(AddComponent<Projection>(fov, window_size, near, far))
        { }
    
    Projection& projection;
};

#endif//CAMERA_HPP_
