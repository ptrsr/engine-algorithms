#include "engine.hpp"

#include <iostream>

#include <glbinding/gl/gl.h>
#include <GLFW/glfw3.h>
#include <glbinding/glbinding.h>

using namespace gl;
using namespace glbinding;

//#endif//HEADLESS

Engine::Engine()
    : scene(std::make_unique<Scene>()) 
{
#ifndef HEADLESS
    std::cout << "Initializing GLFW..." << std::endl;
    if (!glfwInit()) {
        std::cerr << "Could not init GLFW. Exiting..." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Initializing GLbinding..." << std::endl;
    glbinding::initialize(glfwGetProcAddress);
#endif//HEADLESS
}

Engine::~Engine() {
#ifndef HEADLESS
    glfwTerminate();
#endif//HEADLESS
}

void Engine::Update(UpdateContext& context) {
        for (auto& pair : *this) {
            pair.second->Update(context);
        }
    }

void Engine::Run() {
    if (running) {
        return;
    }
    running = true;

    UpdateContext context(*scene, 0);
    while (running) {
        Update(context);
    }
}

void Engine::Stop() {
    running = false;
}
