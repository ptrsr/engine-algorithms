#include "options.hpp"
#include <engine/auxiliary/cgetopt.h>

void Options::PrintUsage(FILE* output) {
    Options opts;
    
    fprintf(output, "\
=============== ENGINE ALGORITHMS ===============\n\
Research project on c++ optimization for Saxion\n\
University of applied sciences by Ruud Peters.\n\
\n\
--------------------- USAGE ---------------------\n\
TBD\n\
\n\
-------------------- OPTIONS --------------------\n\
-h                  - Print this message.\n\
-t                  - Track timing.\n\
-v                  - Be verbose.\n\
-f UINT              - amount of frames.\n\
-d UINT              - amount of dynamic objects.\n\
-a UINT              - amount of static objects.\n\
-s UINT              - seed.\n");
    }

Options Options::ParseOptions(int argc, char** const argv) {
    Options opts;
    std::string options = "htvf:d:a:s:";

    int c;
    while ((c = getopt(argc, argv, options.c_str())) != -1) {
        switch (c) {
            // Reminder: add new options to 'options_str' above and print_usage()!
            case 'h': PrintUsage(stdout); exit(0);           break;
            case 'v': opts.verbose      = true;              break;
            case 't': opts.track_timing = true;              break;
            case 'f': opts.frames       = std::stoi(optarg); break;
            case 'd': opts.dynamics     = std::stoi(optarg); break;
            case 'a': opts.statics      = std::stoi(optarg); break;
            case 's': opts.seed         = std::stoi(optarg); break;
            default:
                fprintf(stderr, "\n");
                PrintUsage(stderr);
                exit(1);
        }
    }
    return opts;
}
