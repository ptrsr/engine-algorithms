#include "engine.hpp"

#include <iostream>
#include <engine/input/options.hpp>

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
    /* necessary for ensuring that all OpenGL objects are
       deleted before terminating window */
    scene.reset();

#ifndef HEADLESS

    // terminate window
    glfwTerminate();

#endif//HEADLESS
}

void Engine::Update(UpdateContext& context) {
    const TimeTracker& tracker = profiler.timer.Start("Loop");
    
    // regular update
    for (auto& pair : *this) {
        pair.second->Update(context);
    }

    // late update
    for (auto& pair : *this) {
        pair.second->LateUpdate(context);
    }

    profiler.timer.Stop(tracker);
}

void Engine::Run(const Options& options) {
    if (running) {
        return;
    }
    running = true;

    UpdateContext context(*scene, 0);
    unsigned updates = 0;

    while (running) {
        Update(context);
        updates++;

        if (options.frames != 0 && updates >= options.frames) {
            break;
        }
    }
    profiler.timer.ToOverview().Print();
}

void Engine::Stop() {
    running = false;
}
