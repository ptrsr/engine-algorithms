#include <gtest/gtest.h>

#include <engine/components/hierarchical.hpp>

namespace {
    /* Hierarchical has protected destructor.
       Creating a mock for testing. */
    TEST(HierarchicalTest, AddChild) {
        Hierarchical parent = Hierarchical();

        // no children after init
        auto& children = parent.GetChildren();
        ASSERT_TRUE(children.empty());

        // adding child results in correct parent
        Hierarchical child = Hierarchical();
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

    TEST(HierarchicalTest, GetChild) {
        Hierarchical parent = Hierarchical();
        Hierarchical child = Hierarchical();

        parent.AddChild(child);

        ASSERT_EQ(&child, parent.GetChild());

        // index 1 doesn't exist, returns nullpointer
        ASSERT_FALSE(parent.GetChild(1));
    }

    TEST(HierarchicalTest, GetChildren) {
        Hierarchical parent = Hierarchical();
        Hierarchical child0 = Hierarchical();
        Hierarchical child1 = Hierarchical();

        parent.AddChild(child0);
        parent.AddChild(child1);

        auto children_list = parent.GetChildren();

        ASSERT_EQ(&child0, children_list[0]);
        ASSERT_EQ(&child1, children_list[1]);

    }

    TEST(HierarchicalTest, UnParent) {
        Hierarchical parent = Hierarchical();

        #ifdef DEBUG
        // throw while unparenting when object has no parent
        ASSERT_ANY_THROW(parent.UnParent());
        #endif
        // add child
        Hierarchical child = Hierarchical();
        parent.AddChild(child);
        ASSERT_EQ(1, parent.GetChildren().size());

        // parent has no more children after unparenting child
        child.UnParent();
        ASSERT_EQ(0, parent.GetChildren().size());
        ASSERT_EQ(nullptr, child.GetParent());
    }

    TEST(HierarchicalTest, SwitchParent) {
        Hierarchical parent1 = Hierarchical();
        Hierarchical parent2 = Hierarchical();
        Hierarchical child = Hierarchical();

        parent1.AddChild(child);
        parent2.AddChild(child);

        // adding same child to other parent switches parent
        ASSERT_EQ(&parent2, child.GetParent());
        ASSERT_EQ(0, parent1.GetChildren().size());
        ASSERT_EQ(&child, parent2.GetChild());
    }

    TEST(HierarchicalTest, Destructor) {
        Hierarchical root = Hierarchical();
        Hierarchical child = Hierarchical();
        {
            Hierarchical middle = Hierarchical();
            root.AddChild(middle);
            middle.AddChild(child);
        }
        // child switched to parent's parent when original parent got deleted
        ASSERT_EQ(&root, child.GetParent());
        ASSERT_EQ(&child, root.GetChild());
    }
}
