#include "engine.hpp"

#include <iostream>
#include <GLFW/glfw3.h>
#include <glbinding/glbinding.h>

Engine::Engine()
    : scene(std::make_unique<Scene>()) 
{

    std::cout << "Initializing GLFW..." << std::endl;
    if (!glfwInit()) {
        std::cerr << "Could not init GLFW. Exiting..." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Initializing GLbinding..." << std::endl;
    glbinding::initialize(glfwGetProcAddress);
}

Engine::~Engine() {
    glfwTerminate();
}

void Engine::Run() {
    if (running) {
        return;
    }
    running = true;
    while (running) {
        Update();
    }
}

void Engine::Stop() {
    running = false;
}
