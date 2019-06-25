#ifndef OPTIONS_HPP_
#define OPTIONS_HPP_

#include <string>
#include <stdio.h>

#ifndef RESOURCE_DIR
#define RESOURCE_DIR
#endif

typedef struct Options { 
	Options() // default options
		: track_timing(false)
		, verbose(false)
		, frames(500)
		, resource_dir(RESOURCE_DIR)
		{ }

	// options
	bool         track_timing;
	bool         verbose;
	unsigned     frames;
	std::string  resource_dir;

    static void PrintUsage(FILE* output = stdout);
    static Options ParseOptions(int argc, char** const argv);

} Options;

#endif//OPTIONS_HPP_
