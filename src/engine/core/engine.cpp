#include "engine.hpp"
#include <iostream>

void Engine::Update() { 
    std::cout << "test" << std::endl;
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
