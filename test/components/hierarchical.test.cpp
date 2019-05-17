#include <gtest/gtest.h>

#include <engine/components/hierarchical.hpp>

namespace {
    TEST(Hierarchical, AddChild) {
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
        // (GetChildren returned a const ref)
        ASSERT_EQ(1, children.size());

        // child in children list is indeed same child
        ASSERT_EQ(&child, &children[0].get());
        ASSERT_EQ(&parent, children[0].get().GetParent());
    }

    TEST(Hierarchical, UnParent) {
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
}

// TEST(Transform, Unparent) {
//     World world;    
//     Transform_ptr parent = world.CreateTransform();
//     Transform_ptr child1 = world.CreateTransform(); 
//     Transform_ptr child2 = world.CreateTransform();

//     parent->AddChild(child1);
//     parent->AddChild(child2);
//     child1->UnParent();

//     // child1 has no more parent
//     ASSERT_FALSE(child1->GetParent());

//     // proper child was removed
//     ASSERT_EQ(parent->GetChildren().size(), 1);
//     ASSERT_EQ(parent->GetChildren()[0], child2);

//     // child2 kept parent
//     ASSERT_EQ(child2->GetParent(), parent);
// }

// TEST(Transform, Switch_parent) {
//     World world;
//     Transform_ptr original = world.CreateTransform(); 
//     Transform_ptr other = world.CreateTransform(); 
//     Transform_ptr child = world.CreateTransform();

//     original->AddChild(child);
//     other->AddChild(child);

//     // original does not have the child anymore
//     ASSERT_TRUE(original->GetChildren().empty());

//     // child on other parent switched correctly
//     ASSERT_EQ(other->GetChildren()[0], child);
// }