#ifndef OPTIONS_HPP_
#define OPTIONS_HPP_

#include <string>
#include <stdio.h>

typedef struct Options { 
	Options() // default options
		: track_timing(false)
		, verbose(false)
		, frames(500)
		{ }

	// options
	bool     track_timing;
	bool     verbose;
	unsigned frames;

    static void PrintUsage(FILE* output = stdout);
    static Options ParseOptions(int argc, char** const argv);

} Options;

#endif//OPTIONS_HPP_
