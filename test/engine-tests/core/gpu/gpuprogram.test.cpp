#include <gtest/gtest.h>

#include <engine/input/file.hpp>
#include <engine/core/gpu/shader.hpp>
#include <engine/core/gpu/gpuprogram.hpp>

namespace {
    TEST(GpuProgramTest, Constructor) {
        File vert_file(std::string(TEST_RESOURCE_DIR) + "engine-test-resources/color.vs");
        Shader_ptr vert_shader = Shader::Make(vert_file.content, Shader::vertex);
        
        File frag_file(std::string(TEST_RESOURCE_DIR) + "engine-test-resources/color.fs");
        Shader_ptr frag_shader = Shader::Make(frag_file.content, Shader::fragment);

        GpuProgram gpu_program({ vert_shader, frag_shader });

        // GpuProgram has id that isn't 0 (null)
        ASSERT_NE(0, gpu_program.id);
    }
}
