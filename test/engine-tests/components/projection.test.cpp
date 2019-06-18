#include <gtest/gtest.h>
#include <engine/components/projection.hpp>

#include <auxiliary/mat.aux.hpp>

TEST(ProjectionTest, Constructor) {
    // camera projection matrix corresponds to input parameters
    Projection projection(nullptr, glm::radians(60.f), glm::vec2(1280, 720), 1.f, 1000.f);

    EXPECT_TRUE(CompareMats(glm::transpose(glm::mat4(
        0.97428, 0,      0,     0,
        0,       1.7321, 0,     0,
        0,       0,     -1.002, -2.002,
        0,       0,     -1,     0)
        ), projection.GetPerspective(), 0.0001f));

#ifdef DEBUG
    ASSERT_ANY_THROW(Projection(nullptr, 0.f, glm::vec2(1280, 720), 1.f, 1000.f));
    ASSERT_ANY_THROW(Projection(nullptr, glm::radians(60.f), glm::vec2(1280, 720), 0.f, 1000.f));
    ASSERT_ANY_THROW(Projection(nullptr, glm::radians(60.f), glm::vec2(1280, 720), 10.f, 1.f));
#endif
}
