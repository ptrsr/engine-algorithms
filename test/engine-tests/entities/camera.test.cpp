#include <gtest/gtest.h>

#include <engine/entities/camera.hpp>

namespace {
    TEST(CameraTest, Constructor) {
        Camera camera(0, glm::radians(60.f), glm::vec2(1280, 720), 1.f, 1000.f);

        // context has been correctly forwarded
        ASSERT_EQ(1, camera.projection.GetNear());
        ASSERT_EQ(1000, camera.projection.GetFar());
        ASSERT_EQ(glm::radians(60.f), camera.projection.GetFov());
        ASSERT_EQ(glm::vec2(1280, 720), camera.projection.GetWindowSize());
    }
}
