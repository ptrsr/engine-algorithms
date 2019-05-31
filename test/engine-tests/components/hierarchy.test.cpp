#include <gtest/gtest.h>

#include <engine/components/hierarchy.hpp>

namespace {
    /* Hierarchy has protected destructor.
       Creating a mock for testing. */
    TEST(HierarchyTest, AddChild) {
        Hierarchy parent = Hierarchy();

        // no children after init
        auto& children = parent.GetChildren();
        ASSERT_TRUE(children.empty());

        // adding child results in correct parent
        Hierarchy child = Hierarchy();
        parent.AddChild(child);
        ASSERT_EQ(&parent, child.GetParent());

        #ifdef DEBUG
        // child cannot be added again
        ASSERT_ANY_THROW(parent.AddChild(child));
        #endif
        // child is in children list
        ASSERT_EQ(1, children.size());

        // child in children list is indeed same child
        ASSERT_EQ(&child, children[0]);
        ASSERT_EQ(&parent, children[0]->GetParent());
    }

    TEST(HierarchyTest, GetChild) {
        Hierarchy parent = Hierarchy();
        Hierarchy child = Hierarchy();

        parent.AddChild(child);

        ASSERT_EQ(&child, parent.GetChild());

        // index 1 doesn't exist, returns nullpointer
        ASSERT_FALSE(parent.GetChild(1));
    }

    TEST(HierarchyTest, GetChildren) {
        Hierarchy parent = Hierarchy();
        Hierarchy child0 = Hierarchy();
        Hierarchy child1 = Hierarchy();

        parent.AddChild(child0);
        parent.AddChild(child1);

        auto children_list = parent.GetChildren();

        ASSERT_EQ(&child0, children_list[0]);
        ASSERT_EQ(&child1, children_list[1]);
    }

    TEST(HierarchyTest, UnParent) {
        Hierarchy parent = Hierarchy();

        #ifdef DEBUG
        // throw while unparenting when object has no parent
        ASSERT_ANY_THROW(parent.UnParent());
        #endif
        // add child
        Hierarchy child = Hierarchy();
        parent.AddChild(child);
        ASSERT_EQ(1, parent.GetChildren().size());

        // parent has no more children after unparenting child
        child.UnParent();
        ASSERT_EQ(0, parent.GetChildren().size());
        ASSERT_EQ(nullptr, child.GetParent());
    }

    TEST(HierarchyTest, SwitchParent) {
        Hierarchy parent1 = Hierarchy();
        Hierarchy parent2 = Hierarchy();
        Hierarchy child = Hierarchy();

        parent1.AddChild(child);
        parent2.AddChild(child);

        // adding same child to other parent switches parent
        ASSERT_EQ(&parent2, child.GetParent());
        ASSERT_EQ(0, parent1.GetChildren().size());
        ASSERT_EQ(&child, parent2.GetChild());
    }

    TEST(HierarchyTest, Destructor) {
        Hierarchy root = Hierarchy();
        Hierarchy child = Hierarchy();
        {
            Hierarchy middle = Hierarchy();
            root.AddChild(middle);
            middle.AddChild(child);
        }
        // child switched to parent's parent when original parent got deleted
        ASSERT_EQ(&root, child.GetParent());
        ASSERT_EQ(&child, root.GetChild());
    }
}
