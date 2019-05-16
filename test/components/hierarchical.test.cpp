#include <gtest/gtest.h>

#include <engine/components/hierarchical.hpp>

TEST(Hierarchical, AddChild) {
    Hierarchical parent = Hierarchical();

    // no children after init
    auto& children = parent.GetChildren();
    ASSERT_TRUE(children.empty());

    // adding child results in correct parent
    Hierarchical child = Hierarchical();
    parent.AddChild(child);
    ASSERT_EQ(child.GetParent(), &parent);

    // child cannot be added again
    ASSERT_ANY_THROW(parent.AddChild(child));

    // child is in children list
    // (GetChildren returned a const ref)
    ASSERT_EQ(children.size(), 1);

    // child in children list is indeed same child
    ASSERT_EQ(&children[0].get(), &child);
    ASSERT_EQ(children[0].get().GetParent(), &parent);
}

TEST(Hierarchical, UnParent) {
    Hierarchical parent = Hierarchical();

    // throw while unparenting when object has no parent
    ASSERT_ANY_THROW(parent.UnParent());

    // add child
    Hierarchical child = Hierarchical();
    parent.AddChild(child);
    ASSERT_EQ(parent.GetChildren().size(), 1);

    // parent has no more children after unparenting child
    child.UnParent();
    ASSERT_EQ(parent.GetChildren().size(), 0);
    ASSERT_EQ(child.GetParent(), nullptr);
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