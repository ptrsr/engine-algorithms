#include <gtest/gtest.h>

#include <engine/components/hierarchical.hpp>

namespace {
    /* Hierarchical has protected destructor.
       Creating a mock for testing. */
    class MockHierarchical : public Hierarchical {
    public:
        ~MockHierarchical() = default;
     };

    TEST(Hierarchical, AddChild) {
        MockHierarchical parent = MockHierarchical();

        // no children after init
        auto& children = parent.GetChildren();
        ASSERT_TRUE(children.empty());

        // adding child results in correct parent
        MockHierarchical child = MockHierarchical();
        parent.AddChild(child);
        ASSERT_EQ(&parent, child.GetParent());

        #ifdef DEBUG
        // child cannot be added again
        ASSERT_ANY_THROW(parent.AddChild(child));
        #endif
        // child is in children list
        ASSERT_EQ(1, children.size());

        // child in children list is indeed same child
        ASSERT_EQ(&child, &children[0].get());
        ASSERT_EQ(&parent, children[0].get().GetParent());
    }

    TEST(Hierarchical, GetChild) {
        MockHierarchical parent = MockHierarchical();
        MockHierarchical child = MockHierarchical();

        parent.AddChild(child);

        ASSERT_EQ(&child, parent.GetChild());

        // index 1 doesn't exist, returns nullpointer
        ASSERT_FALSE(parent.GetChild(1));
    }

    TEST(Hierarchical, UnParent) {
        MockHierarchical parent = MockHierarchical();

        #ifdef DEBUG
        // throw while unparenting when object has no parent
        ASSERT_ANY_THROW(parent.UnParent());
        #endif
        // add child
        MockHierarchical child = MockHierarchical();
        parent.AddChild(child);
        ASSERT_EQ(1, parent.GetChildren().size());

        // parent has no more children after unparenting child
        child.UnParent();
        ASSERT_EQ(0, parent.GetChildren().size());
        ASSERT_EQ(nullptr, child.GetParent());
    }

    TEST(Hierarchical, SwitchParent) {
        MockHierarchical parent1 = MockHierarchical();
        MockHierarchical parent2 = MockHierarchical();
        MockHierarchical child = MockHierarchical();

        parent1.AddChild(child);
        parent2.AddChild(child);

        // adding same child to other parent switches parent
        ASSERT_EQ(&parent2, child.GetParent());
        ASSERT_EQ(0, parent1.GetChildren().size());
        ASSERT_EQ(&child, parent2.GetChild());
    }

    TEST(Hierarchical, Destructor) {
        MockHierarchical root = MockHierarchical();
        MockHierarchical child = MockHierarchical();
        {
            MockHierarchical middle = MockHierarchical();
            root.AddChild(middle);
            middle.AddChild(child);
        }
        // child switched to parent's parent when original parent got deleted
        ASSERT_EQ(&root, child.GetParent());
        ASSERT_EQ(&child, root.GetChild());
    }
}
