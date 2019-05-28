#include <gtest/gtest.h>
#include <core/camera.hpp>

#include <auxiliary/mat.aux.hpp>

TEST(Camera, Init) {
    Camera camera = Camera(glm::radians(60.f), glm::vec2(1280, 720), 1, 1000);

    // camera projection matrix corresponds to input parameters
    ASSERT_TRUE(CompareMats(glm::transpose(glm::mat4(
        0.97428, 0,      0,     0,
        0,       1.7321, 0,     0,
        0,       0,     -1.002, -2.002,
        0,       0,     -1,     0)
        ), camera.GetProjection(), 0.0001f));
}
