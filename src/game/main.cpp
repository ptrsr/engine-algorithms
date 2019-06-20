#include <engine/auxiliary/options.hpp>

#include <game/game.hpp>

int main(int argc, char** argv) {
    Options opts = Options::ParseOptions(argc, argv);

    Engine_ptr engine = std::make_unique<Game>();
    engine->Run(opts.frames);

    return 0;
}

