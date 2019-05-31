#include <gtest/gtest.h>
#include <engine/components/projection.hpp>

#include <auxiliary/mat.aux.hpp>

TEST(ProjectionTest, Init) {
    ProjectionContext context(glm::radians(60.f), glm::vec2(1280, 720), 1, 1000);

    // camera projection matrix corresponds to input parameters
    ASSERT_TRUE(CompareMats(glm::transpose(glm::mat4(
        0.97428, 0,      0,     0,
        0,       1.7321, 0,     0,
        0,       0,     -1.002, -2.002,
        0,       0,     -1,     0)
        ), Projection(context).perspective, 0.0001f));

    ASSERT_DEBUG_DEATH(ProjectionContext(0, glm::vec2(1280, 720), 1, 1000), "fov > 0");
    ASSERT_DEBUG_DEATH(ProjectionContext(glm::radians(60.f), glm::vec2(1280, 720), 0, 1000), "near > 0");
    ASSERT_DEBUG_DEATH(ProjectionContext(glm::radians(60.f), glm::vec2(1280, 720), 10, 1), "far > near");
}
