#include <gtest/gtest.h>

#include <engine/input/file.hpp>

namespace {
    TEST(FileTest, Constructor) {
        File file(std::string(TEST_RESOURCE_DIR) + "engine-test-resources/filetest.txt");

        ASSERT_EQ("test123", file.content);
        ASSERT_EQ("txt", file.extention);
    }
}
