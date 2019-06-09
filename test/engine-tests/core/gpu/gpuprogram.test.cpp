#include <gtest/gtest.h>

#include <engine/core/gpu/gpuprogram.hpp>

#include <iostream>

TEST(GpuProgramTest, Constructor) {
    GpuProgram gpu_program = GpuProgram();

    ASSERT_NE(-1, gpu_program.id);
}
