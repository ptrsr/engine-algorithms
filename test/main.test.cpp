#include <gtest/gtest.h>

// test resources
#ifndef TEST_RESOURCE_DIR
#define TEST_RESOURCE_DIR
#endif

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
