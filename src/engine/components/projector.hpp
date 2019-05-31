#ifndef PROJECTOR_HPP_
#define PROJECTOR_HPP_

#include <engine/core/component.hpp>
#include <engine/glm.hpp>


class Projector : public Component {
public:
    struct Context {
        Context(const float fov, const glm::vec2 windowSize, const float near, const float far);

        const glm::vec2 windowSize;
        const float fov;
        
        const float near;
        const float far;
    };

    Projector(const Context& context, Entity* const entity = nullptr);
    
    const glm::mat4 projection;
    const Context context;
};

#endif // PROJECTOR_HPP_
