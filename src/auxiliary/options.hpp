#ifndef OPTIONS_HPP_
#define OPTIONS_HPP_

#include <string>
#include "c_getopt.h"
#include <stdio.h>

typedef struct Options { Options() :
	// default values
	track_timing(false),
	verbose(false) { }

	// options
	bool track_timing;
	bool verbose;

    static void PrintUsage(FILE* output = stdout) {
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
    -v                  - Be verbose.\n"
        );
    }

    static Options ParseOptions(int argc, char** argv) {
        printf("hello!");

        Options opts;
        std::string options = "htv";

        int c;
        while ((c = getopt(argc, argv, options.c_str())) != -1) {
            const char* test = (char*)c;
            printf("hello!");
            printf(test);
            switch (c) {
                // Reminder: add new options to 'options_str' above and print_usage()!
                case 'h': PrintUsage(stdout); exit(0); break;
                case 'v': opts.verbose      = true; break;
                case 't': opts.track_timing = true; break;
                default:
                    fprintf(stderr, "\n");
                    PrintUsage(stderr);
                    exit(1);
            }
        }
        return opts;
    }
} Options;

#endif // OPTIONS_HPP_
