#include <gtest/gtest.h>

#include <engine/components/mesh.hpp>
#include <engine/input/model.hpp>
#include <engine/components/material.hpp>

#include <glbinding/glbinding.h>

#include <iostream>

namespace {
    TEST(BufferTest, Constructor) {
        std::vector<glm::vec3> data = { glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 0) };
        Buffer<glm::vec3> buffer(data, GL_ARRAY_BUFFER, 3, false);

        ASSERT_NE(0, buffer.id);
    }

    TEST(BufferTest, Bind) {
        Material material(std::string(TEST_RESOURCE_DIR) + "cube");

        std::vector<glm::vec3> data = { glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 0) };

        Buffer<glm::vec3> vertex_buffer(data, GL_ARRAY_BUFFER, 3, false);
        
        ASSERT_TRUE(vertex_buffer.Bind(material.GetAttribute("vertex"), 3));
        ASSERT_TRUE(vertex_buffer.UnBind());
    }

    TEST(MeshTest, Constructor) {
        Model_ptr model = std::make_shared<Model>();
        model->indices = { 1, 2, 3 };
        model->vertices = { glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(1, 1, 0) };
        model->uvs = { glm::vec2(0, 0), glm::vec2(0, 1), glm::vec2(1, 1) };
        // skipping normals

        Mesh mesh(model);
        
        ASSERT_NE(0, mesh.index_buffer.id);
        ASSERT_NE(0, mesh.vertex_buffer.id);
        ASSERT_NE(0, mesh.uv_buffer.id);
        
        // equal to 0 since there wasn't any normal data
        ASSERT_EQ(0, mesh.normal_buffer.id);
    }
}
