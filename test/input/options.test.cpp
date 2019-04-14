#include <gtest/gtest.h>
#include <input/options.hpp>

TEST(Options, Default_Init) {
	Options opts = Options();
	EXPECT_FALSE(opts.verbose);
	EXPECT_FALSE(opts.track_timing);
}

TEST(Options, Parse) {
	const char* args[3] = {"app_name", "-t", "-v" };
	Options opts = Options::ParseOptions(3, (char**)args);
	EXPECT_TRUE(opts.verbose);
	EXPECT_TRUE(opts.track_timing);
}