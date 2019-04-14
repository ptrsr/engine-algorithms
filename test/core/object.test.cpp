#include <gtest/gtest.h>
#include <core/object.hpp>
#include <iostream>
#include <exception>

#include <auxiliary/mat.aux.hpp>

TEST(Object, Init) {
    // assert init with no parameters means unit mat4
    Object object = Object();
    ASSERT_EQ(object.transform, glm::mat4(1));

    // assert init with mat
    object = Object(glm::mat4(2));
    ASSERT_EQ(object.transform, glm::mat4(2));
}

TEST(Object, Position) {
    Object_ptr object = std::make_shared<Object>();
    ASSERT_EQ(object->GetPosition(), glm::vec3());

    // assert if position is set
    object->SetPosition(glm::vec3(1, 2, 3));
    ASSERT_EQ(object->GetPosition(), glm::vec3(1, 2, 3));

    // assert if right column is set
    ASSERT_EQ(object->GetTransform()[3], glm::vec4(object->GetPosition(), 1));
}

TEST(Object, rotation) {
    Object_ptr object = std::make_shared<Object>();
    object->Rotate(glm::pi<float>(), glm::vec3(0, 1, 0));


    glm::mat2 test(1,2,3,4);
    std::cout << test << std::endl;
    EXPECT_TRUE(CompareVecsAbs(glm::mat<2, 2, float>(1.0003f,1.f,1.f,1.f), glm::mat<2, 2, float>(3.f,1.f,1.000006f,6.f), 1.f));
    // std::cout << object->GetTransform() << std::endl;
    // std::cout << glm::mat4(-1, 0, 0, 0,
    //                0, 1, 0, 0,
    //                0, 0,-1, 0,
    //                0, 0, 0, 1) << std::endl;

    // glm::mat4

    // ASSERT_NEAR(object->GetTransform(), 
    //     glm::mat4(-1, 0, 0, 0,
    //                0, 1, 0, 0,
    //                0, 0,-1, 0,
    //                0, 0, 0, 1), 0.000001f
    // );

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
    {
        Object_ptr child = std::make_shared<Object>();
        parent->AddChild(child);

        // assert if two shared pointers exist
        ASSERT_EQ(parent->GetChildren()[0].use_count(), 2);
    }
    // assert after closing scope if pointer count drops to one
    ASSERT_EQ(parent->GetChildren()[0].use_count(), 1);
}

