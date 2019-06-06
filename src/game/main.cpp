#include <engine/auxiliary/options.hpp>
#include <game/game.hpp>

static Engine_ptr engine; 

int main(int argc, char** argv) {
    Options opts = Options::ParseOptions(argc, argv);

    engine = std::make_unique<Game>();
    engine->Run();

    return 0;
}

void quitproc() {
    engine->Stop();
}
