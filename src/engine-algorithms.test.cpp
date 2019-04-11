#include <auxiliary/options.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    Options options = Options::ParseOptions(argc, argv);
    std::cout << options.verbose << std::endl;
}
