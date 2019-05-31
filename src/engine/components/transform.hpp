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
    virtual Component* Clone() override;

public:
    ~Transform() = default;
    Transform(Entity* const entity);
    Transform(glm::mat4 init_mat = glm::mat4(1), Entity* const entity = nullptr);

    // position
    glm::vec3 GetPosition() const;
    void SetPosition(const glm::vec3& position);
    void Translate(const glm::vec3& translation);

    void Rotate(const float angle, const glm::vec3& axis);

};

#endif//TRANSFORM_HPP_
