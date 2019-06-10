#include "window.hpp"

#include <iostream>
#include <GLFW/glfw3.h>

GLFWwindow_ptr Window::CreateWindow(unsigned int width, unsigned int height, std::string title) {
    return GLFWwindow_ptr(
        glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr), 
        [](GLFWwindow* window) { glfwDestroyWindow(window); }
    );
}

Window::Window(Entity* entity, unsigned int width, unsigned int height, std::string title)
    : Component(entity)
    , context(CreateWindow(width, height, title)) 
{ 
    if (!context) {
        std::cerr << "Could not init window. Exiting..." << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}
