#include "game.hpp"

#include <engine/entities/camera.hpp>
#include <engine/components/projector.hpp>
#include <engine/auxiliary/options.hpp>

Game::Game(const Options& options) {
    
    Projector::Context Context(glm::radians(60.f), glm::vec2(1280, 720), 1, 1000);
    Camera& camera = scene->AddEntity<Camera>(Context);
}