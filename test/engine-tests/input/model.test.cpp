#include <gtest/gtest.h>

#include <engine/input/model.hpp>

#include <fstream>

TEST(ModelTest, Constructor) {
    std::string model_path = std::string(TEST_RESOURCE_DIR) +
        "engine-test-resources/test-model.obj";

    std::ifstream file(model_path, std::ios::in);
    Model_ptr model = Model::FromOBJ(file);
    file.close();

    EXPECT_EQ(672, model->indices.size());
    EXPECT_EQ(598, model->vertices.size());
    EXPECT_EQ(598, model->normals.size());
    EXPECT_EQ(598, model->uvs.size());
}
