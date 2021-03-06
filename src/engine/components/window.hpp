#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <string>
#include <memory>
#include <functional>

#include <engine/glm.hpp>
#include <engine/core/component.hpp>
#include <iostream>
class GLFWwindow;

typedef std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>> GLFWwindow_ptr;

class Window : public Component {
private:
    GLFWwindow_ptr CreateWindow(unsigned width, unsigned height, std::string title);

public:
    const GLFWwindow_ptr context;

    Window(Entity* entity, unsigned width, unsigned height, std::string title);
    glm::vec2 GetFrameBufferSize() const;
    void SwapBuffer();

};

#endif//WINDOW_HPP_
