#include <gtest/gtest.h>

#include <engine/components/mesh.hpp>
#include <engine/input/model.hpp>

#include <glbinding/glbinding.h>

TEST(MeshTest, Constructor) {
    Model model;
    model.indices = { 1, 2, 3 };
    model.vertices = { glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 0) };
    model.uvs = { glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 1) };
    // skipping normals

    Mesh mesh(model);

    ASSERT_NE(0, mesh.index_buffer_id);
    ASSERT_NE(0, mesh.vertex_buffer_id);
    ASSERT_NE(0, mesh.uv_buffer_id);
    
    // equal to -1 since there wasn't any normal data
    ASSERT_EQ(0, mesh.normal_buffer_id);
}
