#include <gtest/gtest.h>
#include <core/world.hpp>
#include <core/object.hpp>

TEST(World, Add) {
    World world = World();
    Object_ptr object = std::make_shared<Object>();

    // adding an object to the world
    world.Add(object);

    ASSERT_EQ(world.GetChildren().size(), 1);
}
