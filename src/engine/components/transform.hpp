#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include <vector>
#include <memory>

#include <engine/glm.hpp>
#include <engine/core/component.hpp>

#include <iostream>

class Transform : public Component, public glm::mat4 {
private:
    glm::mat4& transform;

protected:
    virtual Component_ptr Clone(Entity* const entity) override;

public:
    ~Transform() = default;
    Transform(Entity* const entity = nullptr, const glm::mat4& init_mat = glm::mat4(1));

    // position
    glm::vec3 GetPosition() const;
    void SetPosition(const glm::vec3& position);
    void Translate(const glm::vec3& translation);

    void Rotate(const float angle, const glm::vec3& axis);

};

#endif//TRANSFORM_HPP_
