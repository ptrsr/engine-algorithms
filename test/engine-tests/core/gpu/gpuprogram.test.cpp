#include <gtest/gtest.h>

#include <engine/input/file.hpp>
#include <engine/core/gpu/shader.hpp>
#include <engine/core/gpu/gpuprogram.hpp>

namespace {
    static File vert_file(std::string(TEST_RESOURCE_DIR) + "engine-test-resources/color.vs");

    TEST(GpuProgramTest, Constructor) {
        Shader_ptr vert_shader = Shader::Make(vert_file.content, Shader::vertex);
        
        File frag_file(std::string(TEST_RESOURCE_DIR) + "engine-test-resources/color.fs");
        Shader_ptr frag_shader = Shader::Make(frag_file.content, Shader::fragment);

        std::vector<Shader_ptr> shaders = { vert_shader, frag_shader };
        GpuProgram_ptr gpu_program = GpuProgram::Make(shaders);

        // GpuProgram has id that isn't 0 (null)
        ASSERT_NE(0, gpu_program->id);
    }

    TEST(GpuProgramTest, GetFields) {
        Shader_ptr vert_shader = Shader::Make(vert_file.content, Shader::vertex);
        
        // only linking vertex shader
        std::vector<Shader_ptr> shaders = { vert_shader };
        GpuProgram_ptr gpu_program = GpuProgram::Make(shaders);

        // getting non existing field results in id of -1
        EXPECT_EQ(-1, gpu_program->GetUniform("wrong_uniform"));
        EXPECT_EQ(-1, gpu_program->GetAttribute("wrong_attrib"));
        
        // valid fields have id's starting from 0
        EXPECT_NE(-1, gpu_program->GetUniform("model_mat"));
        EXPECT_NE(-1, gpu_program->GetUniform("view_mat"));
        EXPECT_NE(-1, gpu_program->GetUniform("proj_mat"));

        EXPECT_NE(-1, gpu_program->GetAttribute("vertex"));
    }
}
