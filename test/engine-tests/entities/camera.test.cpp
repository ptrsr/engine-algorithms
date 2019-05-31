#include <gtest/gtest.h>

#include <engine/entities/camera.hpp>

TEST(CameraTest, Init) {

    ProjectionContext context(glm::radians(60.f), glm::vec2(1280, 720), 1, 1000);
    Camera camera = Camera(0, context);

    // context has been correctly forwarded
    ASSERT_EQ(context.near, camera.projection.near);
    ASSERT_EQ(context.far, camera.projection.far);
    ASSERT_EQ(context.fov, camera.projection.fov);
    ASSERT_EQ(context.windowSize, camera.projection.windowSize);
}
