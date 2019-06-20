#include "window.hpp"

#include <iostream>
#include <GLFW/glfw3.h>
#include <glbinding/glbinding.h>

GLFWwindow_ptr Window::CreateWindow(unsigned width, unsigned height, std::string title) {
    return GLFWwindow_ptr(
        glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr), 
        [](GLFWwindow* window) { glfwDestroyWindow(window); }
    );
}

Window::Window(Entity* entity, unsigned width, unsigned height, std::string title)
    : Component(entity)
    , context(CreateWindow(width, height, title)) 
{ 
    if (!context) {
        std::cerr << "Could not init window. Exiting..." << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(context.get());

    std::cout << "Initializing GLbinding..." << std::endl;
    glbinding::initialize([](const char * name) {
        return glfwGetProcAddress(name);
    });

    glfwSwapInterval(1);
    std::cout << "initialized!" << std::endl;
}

glm::vec2 Window::GetFrameBufferSize() {
    int width, height;
    glfwGetFramebufferSize(context.get(), &width, &height);
    return glm::vec2(width, height);
}

void Window::SwapBuffer() {
    glfwSwapBuffers(context.get());
    glfwPollEvents();
}
