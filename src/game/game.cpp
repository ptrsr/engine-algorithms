#include "game.hpp"

#include <engine/auxiliary/options.hpp>
#include <engine/entities/camera.hpp>
#include <engine/components/projection.hpp>

Game::Game(const Options& options) {
    Camera& camera = scene->AddEntity<Camera>(
        ProjectionContext(glm::radians(60.f), glm::vec2(1280, 720), 1, 1000)
    );

}
