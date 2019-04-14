#include <gtest/gtest.h>
#include <core/object.hpp>
#include <iostream>
#include <exception>

#include <auxiliary/mat.aux.hpp>

TEST(Object, Init) {
    // assert init with no parameters means unit mat4
    Object object = Object();
    ASSERT_EQ(object.GetTransform(), glm::mat4(1));

    // assert init with mat
    object = Object(glm::mat4(2));
    ASSERT_EQ(object.GetTransform(), glm::mat4(2));
}

TEST(Object, Position) {
    Object_ptr object = std::make_shared<Object>();
    ASSERT_EQ(object->GetPosition(), glm::vec3());

    // assert if position is set
    object->SetPosition(glm::vec3(1, 2, 3));
    ASSERT_EQ(object->GetPosition(), glm::vec3(1, 2, 3));

    // assert if right column is set
    ASSERT_EQ(object->GetTransform()[3], glm::vec4(object->GetPosition(), 1));
    
    // assert if rest of matrix is not adjusted
    ASSERT_TRUE(CompareMats(glm::transpose(glm::mat4(
         1,  0,  0,  1,
         0,  1,  0,  2,
         0,  0,  1,  3,
         0,  0,  0,  1
        )), object->GetTransform(), 0.f));
}

TEST(Object, Translate) {
    Object_ptr object = std::make_shared<Object>();

    object->Translate(glm::vec3(1, 2, 3));
    ASSERT_EQ(object->GetPosition(), glm::vec3(1, 2, 3));

    object->Translate(glm::vec3(3, 2, 1));
    ASSERT_EQ(object->GetPosition(), glm::vec3(4, 4, 4));

    // assert if rest of matrix is not adjusted
    ASSERT_TRUE(CompareMats(glm::transpose(glm::mat4(
         1,  0,  0,  4,
         0,  1,  0,  4,
         0,  0,  1,  4,
         0,  0,  0,  1
    )), object->GetTransform(), 0.f));
}

TEST(Object, rotation) {
    Object_ptr object = std::make_shared<Object>();
    
    // new object should have identity matrix
    ASSERT_TRUE(CompareMats(object->GetTransform(), glm::mat4(1), TRIG_DIF));
    
    // rotating by pi should negate x and z vectors
    object->Rotate(glm::pi<float>(), glm::vec3(0, 1, 0));
    ASSERT_TRUE(CompareMats(glm::mat4(
        -1,  0,  0,  0,
         0,  1,  0,  0,
         0,  0, -1,  0,
         0,  0,  0,  1
        ), object->GetTransform(), TRIG_DIF));

    // half a flip over X axis
    object->Rotate(glm::pi<float>(), glm::vec3(1, 0, 0));
    ASSERT_TRUE(CompareMats(glm::mat4(
        -1,  0,  0,  0,
         0, -1,  0,  0,
         0,  0,  1,  0,
         0,  0,  0,  1
        ), object->GetTransform(), TRIG_DIF));
}

TEST(Object, Parent) {
    // throw when trying to unparent when object has no parent
    Object_ptr parent = std::make_shared<Object>();
    ASSERT_THROW(parent->UnParent(), std::runtime_error);

    // assert no children after init
    auto& children = parent->GetChildren();
    ASSERT_EQ(children.size(), 0);

    // assert adding child results in correct parent
    Object_ptr child = std::make_shared<Object>();
    parent->AddChild(child);
    ASSERT_EQ(child->GetParent(), parent);

    // assert chilren size 1
    // (GetChildren returned a const ref)
    ASSERT_EQ(children.size(), 1);

    // assert child in children list is indeed same child
    ASSERT_EQ(children[0], child);
    ASSERT_EQ(children[0]->GetParent(), parent);

    // assert if unparenting removes relation in both child and parent
    child->UnParent();
    ASSERT_EQ(children.size(), 0);
    ASSERT_EQ(child->GetParent(), nullptr);
}

TEST(Object, Remove) {

    Object_ptr parent = std::make_shared<Object>();
    Object_ptr child = std::make_shared<Object>();
    
    // assert if only one reference exists
    ASSERT_EQ(child.use_count(), 1);

    uint count;
    // create new scope
    {
        // assert if created new reference
        Object_ptr tmp = child;
        ASSERT_EQ(child.use_count(), 2);

        // assert if adding child creates a third reference
        parent->AddChild(tmp);
        ASSERT_GE(child.use_count(), 3);
        count = child.use_count();
    }
    ASSERT_LT(child.use_count(), count);
    count = child.use_count();

    // assert if unparenting removes reference
    child->UnParent();
    ASSERT_LT(child.use_count(), count);
}
