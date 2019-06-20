#include "engine.hpp"

#include <iostream>

#ifndef HEADLESS

#include <glbinding/gl/gl.h>
#include <GLFW/glfw3.h>
#include <glbinding/glbinding.h>

using namespace gl;
using namespace glbinding;

#endif//HEADLESS

Engine::Engine()
    : scene(std::make_unique<Scene>()) 
    , profiler(scene->AddEntity<Profiler>())
{
#ifndef HEADLESS
   
    std::cout << "Initializing GLFW..." << std::endl;
    if (!glfwInit()) {
        std::cerr << "Could not init GLFW. Exiting..." << std::endl;
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

#endif//HEADLESS
}

Engine::~Engine() {
#ifndef HEADLESS

    /* necessary for ensuring that all OpenGL objects are
       deleted before terminating window */
    scene.reset();

    // terminate window
    glfwTerminate();

#endif//HEADLESS
}

void Engine::Update(UpdateContext& context) {
    const TimeTracker& tracker = profiler.timer.Start("Loop");
    for (auto& pair : *this) {
        pair.second->Update(context);
    }
    profiler.timer.Stop(tracker);
}

void Engine::Run(const unsigned max_updates) {
    if (running) {
        return;
    }
    running = true;

    UpdateContext context(*scene, 0);
    unsigned updates = 0;

    while (running) {
        Update(context);
        updates++;

        if (max_updates != 0 && updates >= max_updates) {
            break;
        }
    }
    profiler.timer.ToOverview().Print();
}

void Engine::Stop() {
    running = false;
}
