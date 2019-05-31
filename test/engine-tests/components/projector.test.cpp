#include <gtest/gtest.h>
#include <engine/components/projector.hpp>

#include <auxiliary/mat.aux.hpp>

TEST(ProjectorTest, Init) {
    Projector::Context context(glm::radians(60.f), glm::vec2(1280, 720), 1, 1000);

    // camera projection matrix corresponds to input parameters
    ASSERT_TRUE(CompareMats(glm::transpose(glm::mat4(
        0.97428, 0,      0,     0,
        0,       1.7321, 0,     0,
        0,       0,     -1.002, -2.002,
        0,       0,     -1,     0)
        ), Projector(context).projection, 0.0001f));

    ASSERT_DEBUG_DEATH(Projector::Context(0, glm::vec2(1280, 720), 1, 1000), "fov > 0");
    ASSERT_DEBUG_DEATH(Projector::Context(glm::radians(60.f), glm::vec2(1280, 720), 0, 1000), "near > 0");
    ASSERT_DEBUG_DEATH(Projector::Context(glm::radians(60.f), glm::vec2(1280, 720), 10, 1), "far > near");
}
