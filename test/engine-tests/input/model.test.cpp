#include <gtest/gtest.h>

#include <engine/input/model.hpp>
#include <engine/input/file.hpp>

#include <fstream>
#include <iostream>

namespace {
    TEST(ModelTest, Constructor) {
        Model_ptr model = Model::FromOBJ(File(std::string(TEST_RESOURCE_DIR) + "cube.obj"));

        EXPECT_EQ(36, model->indices.size());
        EXPECT_EQ(24, model->vertices.size());
        EXPECT_EQ(24, model->normals.size());
        EXPECT_EQ(24, model->uvs.size());
    }
}
