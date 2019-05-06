#include <stdio.h>
#include <iostream>
#include <auxiliary/options.hpp>
#include <core/object.hpp>

int main(int argc, char** argv) {

    Options opts = Options::ParseOptions(argc, argv);
    return 0;
}
