#include <gtest/gtest.h>
#include <engine/core/gpu/shader.hpp>
#include <engine/input/file.hpp>

TEST(ShaderTest, Constructor) {

    File file(std::string(TEST_RESOURCE_DIR) + "engine-test-resources/color.vs");

    std::string source = "adsflkjads;lfkj";
    Shader shader = Shader(file.content, Shader::vertex);
}
