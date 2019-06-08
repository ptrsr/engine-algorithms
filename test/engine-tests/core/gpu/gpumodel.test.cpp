#include <gtest/gtest.h>

#include <engine/core/gpu/gpumodel.hpp>

#include <glbinding/glbinding.h>

TEST(GpuModelTest, GenerateBuffer) {
    GpuModel model = GpuModel();

    std::vector<unsigned int> data = { 1, 2, 3, 4, 5, 6, 7, 8 };

    gl::GLuint test = model.GenerateBuffer(data, gl::GL_ELEMENT_ARRAY_BUFFER);
}
