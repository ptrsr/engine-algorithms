#include <gtest/gtest.h>

#include <engine/core/gpu/gpumodel.hpp>
#include <engine/input/model.hpp>

#include <glbinding/glbinding.h>

TEST(GpuModelTest, Constructor) {

    Model model = Model();
    model.indices = { 1, 2, 3 };
    model.vertices = { glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 0) };
    model.uvs = { glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 1) };
    // skipping normals

    GpuModel gpu_model = GpuModel(model);

    ASSERT_NE(-1, gpu_model.index_buffer_id);
    ASSERT_NE(-1, gpu_model.vertex_buffer_id);
    ASSERT_NE(-1, gpu_model.uv_buffer_id);
    
    // equal to -1 since there wasn't any normal data
    ASSERT_EQ(-1, gpu_model.normal_buffer_id);

}
