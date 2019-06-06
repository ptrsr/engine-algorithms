#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <string>
#include <memory>
#include <functional>
#include <engine/core/component.hpp>

class GLFWwindow;

typedef std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> GLFWwindow_ptr;

class Window : public Component {
private:
    GLFWwindow_ptr CreateWindow(unsigned int width, unsigned int height, std::string title);

public:
    const GLFWwindow_ptr context;

    Window(Entity* entity, unsigned int width, unsigned int height, std::string title);


};

#endif//WINDOW_HPP_
