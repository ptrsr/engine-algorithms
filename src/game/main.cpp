#include <stdio.h>
#include <iostream>
#include <engine/auxiliary/options.hpp>
#include <engine/core/engine.hpp>

static Engine_ptr engine; 

int main(int argc, char** argv) {
    Options opts = Options::ParseOptions(argc, argv);

    engine = std::make_unique<Engine>();
    engine->Run();

    return 0;
}

void quitproc() {
    engine->Stop();
}
