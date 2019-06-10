#include <gtest/gtest.h>
#include <engine/core/gpu/shader.hpp>
#include <engine/input/file.hpp>

namespace {
    TEST(ShaderTest, Constructor) {
        File file(std::string(TEST_RESOURCE_DIR) + "engine-test-resources/color.vs");
        Shader_ptr shader = Shader::Make(file.content, Shader::vertex);

        // shader has a uID that isn't 0 (null)
        ASSERT_NE(0, shader->id);
        ASSERT_EQ(Shader::vertex, shader->type);
    }
}
