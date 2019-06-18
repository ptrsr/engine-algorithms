#ifndef PROJECTION_HPP_
#define PROJECTION_HPP_

#include <engine/core/component.hpp>
#include <engine/glm.hpp>
#include <algorithm>

class Projection : public Component {
public:
    Projection(Entity* const entity, const float fov, const glm::vec2& window_size, const float near, const float far);
    Projection(const Projection&) = default;

    glm::vec2 GetWindowSize() const;
    void SetWindowSize(const glm::vec2& window_size);

    float GetFov() const;
    void SetFov(const float fov);

    float GetNear() const;
    void SetNear(const float near);

    float GetFar() const;
    void SetFar(const float far);

    const glm::mat4& GetPerspective() const;

private:
    glm::mat4 perspective;

    glm::vec2 window_size;
    float fov;
    float near;
    float far;

    void Calc();
};

#endif // PROJECTION_HPP_
