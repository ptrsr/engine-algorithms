#include "engine.hpp"

void Engine::Update() { }

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

// void quitproc() {
// 	exit(0);
// }