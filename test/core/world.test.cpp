#include <gtest/gtest.h>

#include <engine/core/world.hpp>
#include <engine/core/object.hpp>

TEST(World, CreateObject) {
    World world = World();

    // create 2 objects    
    Object_ptr obj1 = world.CreateObject();
    Object_ptr obj2 = world.CreateObject();

    // world has 2 objects as children
    auto children = world.GetChildren();
    ASSERT_EQ(children.size(), 2);

    // objects are added to children list in same order of creation
    ASSERT_EQ(children[0], obj1);
    ASSERT_EQ(children[1], obj1);
}

