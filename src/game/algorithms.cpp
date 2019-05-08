#include <stdio.h>
#include <iostream>
#include <engine/auxiliary/options.hpp>
#include <engine/core/object.hpp>

int main(int argc, char** argv) {

    Options opts = Options::ParseOptions(argc, argv);
    return 0;
}
