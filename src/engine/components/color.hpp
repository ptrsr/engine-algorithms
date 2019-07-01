#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <engine/core/component.hpp>
#include <glm/vec3.hpp>

class ColorComponent : public Component {
public:
    glm::vec3 color = glm::vec3(1, 0, 1);
    using Component::Component;
    // ColorComponent(Entity* const entity)
    //     : 
};

#endif//COLOR_HPP_
