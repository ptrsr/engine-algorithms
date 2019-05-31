#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include <engine/core/entity.hpp>
#include <engine/components/window.hpp>

class Display : public Entity {
    Display()
        : window(AddComponent<Window>())
        { }

    Window& window;
};

#endif//DISPLAY_HPP_
