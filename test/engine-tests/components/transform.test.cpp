#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <engine/components/transform.hpp>
#include <engine/core/scene.hpp>
#include <auxiliary/mat.aux.hpp>

#include <exception>
#include <iostream>

namespace {
    // transform test setup
    class TransformTest : public ::testing::Test {
    protected:
        Transform transform;
    };

    TEST_F(TransformTest, Constructor) {
        { // init with no parameters means unit mat4
            ASSERT_TRUE(CompareMats(glm::mat4(1), transform, 0.f));
        }
        { // init with given mat4
            Transform transform_i = Transform(nullptr, glm::mat4(2));
            ASSERT_TRUE(CompareMats(glm::mat4(2), transform_i, 0.f));
        }
    }

    TEST_F(TransformTest, Position) {
        // initial position is (0, 0, 0)
        ASSERT_EQ(glm::vec3(0, 0, 0), transform.GetPosition());

        // position is set
        transform.SetPosition(glm::vec3(1, 2, 3));
        ASSERT_EQ(glm::vec3(1, 2, 3), transform.GetPosition());

        // right column is set
        ASSERT_EQ(transform[3], glm::vec4(transform.GetPosition(), 1));
        
        // rest of matrix is not adjusted
        // (transpose because input is column major)
        ASSERT_TRUE(CompareMats(glm::transpose(glm::mat4(
            1,  0,  0,  1,
            0,  1,  0,  2,
            0,  0,  1,  3,
            0,  0,  0,  1
            )), transform, 0.f));
    }

    TEST_F(TransformTest, Translate) {
        // translating adds vector to position
        transform.Translate(glm::vec3(1, 2, 3));
        ASSERT_EQ(glm::vec3(1, 2, 3), transform.GetPosition());

        transform.Translate(glm::vec3(3, 2, 1));
        ASSERT_EQ(glm::vec3(4, 4, 4), transform.GetPosition());

        // rest of matrix is not adjusted
        // (transpose because input is column major)
        ASSERT_TRUE(CompareMats(glm::transpose(glm::mat4(
            1,  0,  0,  4,
            0,  1,  0,  4,
            0,  0,  1,  4,
            0,  0,  0,  1
        )), transform, 0.f));
    }

    TEST_F(TransformTest, Rotate) {
        // new object should have identity matrix
        ASSERT_TRUE(CompareMats(glm::mat4(1), transform, TRIG_DIF));
        
        // rotating by pi should negate x and z vectors
        transform.Rotate(glm::pi<float>(), glm::vec3(0, 1, 0));
        ASSERT_TRUE(CompareMats(glm::mat4(
           -1,  0,  0,  0,
            0,  1,  0,  0,
            0,  0, -1,  0,
            0,  0,  0,  1
            ), transform, TRIG_DIF));

        // half a flip over X axis
        transform.Rotate(glm::pi<float>(), glm::vec3(1, 0, 0));

        // (no need to transpose, as it's a square matrix)
        ASSERT_TRUE(CompareMats(glm::mat4(
           -1,  0,  0,  0,
            0, -1,  0,  0,
            0,  0,  1,  0,
            0,  0,  0,  1
            ), transform, TRIG_DIF));
    }

    TEST_F(TransformTest, Scale) {
        transform.Scale(glm::vec3(1, 2, 3));
        ASSERT_TRUE(CompareMats(glm::mat4(
            1,  0,  0,  0,
            0,  2,  0,  0,
            0,  0,  3,  0,
            0,  0,  0,  1
            ), transform, TRIG_DIF));

        transform.Scale(glm::vec3(3, 2, 1));
        ASSERT_TRUE(CompareMats(glm::mat4(
            3,  0,  0,  0,
            0,  4,  0,  0,
            0,  0,  3,  0,
            0,  0,  0,  1
            ), transform, TRIG_DIF));
    }
}
