#include "game.hpp"

#include <engine/auxiliary/options.hpp>
#include <engine/entities/display.hpp>

#include <iostream>

Game::Game() {
    scene->AddEntity<Display>();
    
}

void Game::Update() {
    //std::cout << "yes" << std::endl;
}