#include <engine/input/options.hpp>

#include <game/game.hpp>

int main(int argc, char** argv) {
    Options opts = Options::ParseOptions(argc, argv);

    Engine_ptr engine = std::make_unique<Game>(opts);
    engine->Run(opts);

    return 0;
}

