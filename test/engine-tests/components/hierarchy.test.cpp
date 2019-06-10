#include <gtest/gtest.h>

#include <engine/components/hierarchy.hpp>
#include <iostream>

namespace {
    /* Hierarchy has protected destructor.
       Creating a mock for testing. */
    TEST(HierarchyTest, AddChild) {
        Hierarchy parent;

        // no children after init
        auto& children = parent.GetChildren();
        ASSERT_TRUE(children.empty());

        // adding child results in correct parent
        Hierarchy child;
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
        Hierarchy parent, child;

        parent.AddChild(child);

        ASSERT_EQ(&child, parent.GetChild());

        // index 1 doesn't exist, returns nullpointer
        ASSERT_FALSE(parent.GetChild(1));
    }

    TEST(HierarchyTest, GetChildren) {
        Hierarchy parent, child0, child1;

        parent.AddChild(child0);
        parent.AddChild(child1);

        auto children_list = parent.GetChildren();

        ASSERT_EQ(&child0, children_list[0]);
        ASSERT_EQ(&child1, children_list[1]);
    }

    TEST(HierarchyTest, UnParent) {
        Hierarchy parent, child;
        parent.AddChild(child);

        ASSERT_EQ(1, parent.GetChildren().size());

        // parent has no more children after unparenting child
        child.UnParent();
        ASSERT_EQ(0, parent.GetChildren().size());
        ASSERT_EQ(nullptr, child.GetParent());
    }

    TEST(HierarchyTest, SwitchParent) {
        Hierarchy parent1, parent2, child;

        parent1.AddChild(child);
        parent2.AddChild(child);

        // adding same child to other parent switches parent
        ASSERT_EQ(&parent2, child.GetParent());
        ASSERT_EQ(0, parent1.GetChildren().size());
        ASSERT_EQ(&child, parent2.GetChild());
    }

    TEST(HierarchyTest, Root) {
        Hierarchy root;

        Hierarchy parent(nullptr, &root);
        Hierarchy child(nullptr, &root);

        // automatically childed too root
        ASSERT_EQ(2, root.GetChildren().size());

        parent.AddChild(child);

        // child got removed from root and is now childed under parent
        ASSERT_EQ(1, root.GetChildren().size());
        ASSERT_EQ(1, parent.GetChildren().size());

        child.UnParent();

        // unparenting results in root as parent
        ASSERT_EQ(2, root.GetChildren().size());
    }

    TEST(HierarchyTest, Destructor) {
        Hierarchy parent, child;
        {
            Hierarchy middle;
            parent.AddChild(middle);
            middle.AddChild(child);
        }
        // child switched to parent's parent when original parent got deleted
        ASSERT_EQ(&parent, child.GetParent());
        ASSERT_EQ(&child, parent.GetChild());
    }
}
