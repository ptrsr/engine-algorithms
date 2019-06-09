#include <gtest/gtest.h>

#include <engine/input/model.hpp>
#include <engine/input/file.hpp>

#include <fstream>

TEST(ModelTest, Constructor) {

    File file = File(std::string(TEST_RESOURCE_DIR) +
        "engine-test-resources/test-model.obj");

    Model_ptr model = Model::FromOBJ(file.content);

    EXPECT_EQ(672, model->indices.size());
    EXPECT_EQ(598, model->vertices.size());
    EXPECT_EQ(598, model->normals.size());
    EXPECT_EQ(598, model->uvs.size());
}
