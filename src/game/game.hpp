#ifndef GAME_HPP_
#define GAME_HPP_

#include <engine/core/engine.hpp>

class Options;

class Game : public Engine {
public:
    Game(const Options& options);

};

#endif//GAME_HPP_
