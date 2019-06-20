#include <gtest/gtest.h>

#include <engine/input/file.hpp>
#include <engine/components/material.hpp>

namespace {
    TEST(ShaderTest, Constructor) {
        File file(std::string(TEST_RESOURCE_DIR) + "color.vs");
        Shader shader(file.content, Shader::vertex);

        // shader id isn't 0 (null)
        ASSERT_NE(0, shader.id);
        ASSERT_EQ(Shader::vertex, shader.type);
    }

    TEST(MaterialTest, Constructor) {
        File vert_file(std::string(TEST_RESOURCE_DIR) + "color.vs");
        File frag_file(std::string(TEST_RESOURCE_DIR) + "color.fs");

        Material material = Material({
            std::make_shared<Shader>(vert_file.content, Shader::vertex),
            std::make_shared<Shader>(frag_file.content, Shader::fragment),
        });

        // Material has id that isn't 0 (null)
        ASSERT_NE(0, material.id);
    }

    TEST(MaterialTest, GetFields) {
        File vert_file(std::string(TEST_RESOURCE_DIR) + "color.vs");
        File frag_file(std::string(TEST_RESOURCE_DIR) + "color.fs");

        Material material = Material({
            std::make_shared<Shader>(vert_file.content, Shader::vertex),
            std::make_shared<Shader>(frag_file.content, Shader::fragment),
        });

        // Material has id that isn't 0 (null)
        ASSERT_NE(0, material.id);

        // getting non existing field results in id of -1
        EXPECT_EQ(-1, material.GetUniform("wrong_uniform"));
        EXPECT_EQ(-1, material.GetAttribute("wrong_attrib"));
        
        // valid fields
        EXPECT_NE(-1, material.GetUniform("model_mat"));
        EXPECT_NE(-1, material.GetUniform("view_mat"));
        EXPECT_NE(-1, material.GetUniform("proj_mat"));

        EXPECT_NE(-1, material.GetAttribute("vertex"));
    }
}
