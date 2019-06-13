#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include <engine/core/entity.hpp>
#include <engine/components/window.hpp>

class Display : public Entity {
public:
    Display(unsigned int id)
        : Entity(id)
        , window(AddComponent<Window>(1280, 720, "test"))
        { }

    Window& window;
};

#endif//DISPLAY_HPP_
