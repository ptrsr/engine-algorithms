#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include <vector>
#include <memory>
#include <iostream>

#include <engine/glm.hpp>
#include <engine/core/component.hpp>

class Transform;
typedef std::shared_ptr<Transform> Transform_ptr;

class World;
class Transform : public Component, public glm::mat4 {
    public:
        Transform(glm::mat4 init_mat = glm::mat4());

        // position
        glm::vec3 GetPosition() const;
        void SetPosition(const glm::vec3& position);
        void Translate(const glm::vec3& translation);

        void Rotate(const float angle, const glm::vec3& axis);

    private:
        glm::mat4& transform;
};

#endif//TRANSFORM_HPP_
