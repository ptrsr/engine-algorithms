#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <engine/core/world.hpp>
#include <engine/core/object.hpp>
#include <engine/core/message.hpp>
#include <auxiliary/mat.aux.hpp>

#include <exception>
#include <iostream>

TEST(Object, Init) {
    World world;

    // init with no parameters means unit mat4
    Object_ptr object = world.CreateObject();
    ASSERT_EQ(object->GetTransform(), glm::mat4(1));
}

TEST(Object, Position) {
    World world;
    Object_ptr object = world.CreateObject();
    
    // initial position is (0, 0, 0)
    ASSERT_EQ(object->GetPosition(), glm::vec3());

    // position is set
    object->SetPosition(glm::vec3(1, 2, 3));
    ASSERT_EQ(object->GetPosition(), glm::vec3(1, 2, 3));

    // right column is set
    ASSERT_EQ(object->GetTransform()[3], glm::vec4(object->GetPosition(), 1));
    
    // rest of matrix is not adjusted
    // (transpose because input is column major)
    ASSERT_TRUE(CompareMats(glm::transpose(glm::mat4(
         1,  0,  0,  1,
         0,  1,  0,  2,
         0,  0,  1,  3,
         0,  0,  0,  1
        )), object->GetTransform(), 0.f));
}

TEST(Object, Translate) {
    World world;
    Object_ptr object = world.CreateObject();

    // translating adds vector to position
    object->Translate(glm::vec3(1, 2, 3));
    ASSERT_EQ(object->GetPosition(), glm::vec3(1, 2, 3));

    object->Translate(glm::vec3(3, 2, 1));
    ASSERT_EQ(object->GetPosition(), glm::vec3(4, 4, 4));

    // rest of matrix is not adjusted
    // (transpose because input is column major)
    ASSERT_TRUE(CompareMats(glm::transpose(glm::mat4(
         1,  0,  0,  4,
         0,  1,  0,  4,
         0,  0,  1,  4,
         0,  0,  0,  1
    )), object->GetTransform(), 0.f));
}

TEST(Object, rotation) {
    World world;
    Object_ptr object = world.CreateObject();
    
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

    // (no need to transpose, as it's a square matrix)
    ASSERT_TRUE(CompareMats(glm::mat4(
        -1,  0,  0,  0,
         0, -1,  0,  0,
         0,  0,  1,  0,
         0,  0,  0,  1
        ), object->GetTransform(), TRIG_DIF));
}

TEST(Object, Parent) {
    World world;
    // throw while unparenting when object has no parent
    Object_ptr parent = world.CreateObject();
    ASSERT_THROW(parent->UnParent(), std::runtime_error);

    // no children after init
    auto& children = parent->GetChildren();
    ASSERT_TRUE(children.empty());

    // adding child results in correct parent
    Object_ptr child = world.CreateObject();
    parent->AddChild(child);
    ASSERT_EQ(child->GetParent(), parent);

    // child cannot be added again
    ASSERT_THROW(parent->AddChild(child), std::runtime_error);

    // child is in children list
    // (GetChildren returned a const ref)
    ASSERT_EQ(children.size(), 1);

    // child in children list is indeed same child
    ASSERT_EQ(children[0], child);
    ASSERT_EQ(children[0]->GetParent(), parent);
}

TEST(Object, Unparent) {
    World world;    
    Object_ptr parent = world.CreateObject();
    Object_ptr child1 = world.CreateObject(); 
    Object_ptr child2 = world.CreateObject();

    parent->AddChild(child1);
    parent->AddChild(child2);
    child1->UnParent();

    // child1 has no more parent
    ASSERT_FALSE(child1->GetParent());

    // proper child was removed
    ASSERT_EQ(parent->GetChildren().size(), 1);
    ASSERT_EQ(parent->GetChildren()[0], child2);

    // child2 kept parent
    ASSERT_EQ(child2->GetParent(), parent);
}

TEST(Object, Switch_parent) {
    World world;
    Object_ptr original = world.CreateObject(); 
    Object_ptr other = world.CreateObject(); 
    Object_ptr child = world.CreateObject();

    original->AddChild(child);
    other->AddChild(child);

    // original does not have the child anymore
    ASSERT_TRUE(original->GetChildren().empty());

    // child on other parent switched correctly
    ASSERT_EQ(other->GetChildren()[0], child);
}

TEST(Object, Remove) {
    World world;
    Object_ptr obj1 = world.CreateObject();
    Object_ptr obj2 = world.CreateObject();
    Object_ptr obj3 = world.CreateObject();
    Object_ptr obj4 = world.CreateObject();

    // add two children to obj3
    obj3->AddChild(obj1);
    obj3->AddChild(obj2);

    // parent obj4 to obj3
    obj4->AddChild(obj3);
    obj3->Remove();

    // removed object has no more relations
    ASSERT_TRUE(obj3->GetChildren().empty());
    ASSERT_FALSE(obj3->GetParent());

    // children moved to upper parent
    ASSERT_EQ(obj1->GetParent(), obj4);
    ASSERT_EQ(obj2->GetParent(), obj4);

    // final parent has gained the two childeren
    ASSERT_EQ(obj4->GetChildren().size(), 2);

    // not able to remove (non recursively) without parent
    ASSERT_THROW(obj4->Remove(), std::runtime_error);

    // object is deleted after all pointers are lost
    std::weak_ptr<Object> weakptr = obj3;
    obj3 = nullptr;
    ASSERT_TRUE(weakptr.expired());

    // recreate obj3
    obj3 = world.CreateObject();
    obj3->AddChild(obj1);
    obj3->AddChild(obj2);
    obj4->AddChild(obj3);

    // remove all
    obj4->Remove(true);

    // all (nested) childeren have no more parent and children
    std::vector<Object_ptr> objects = {obj1, obj2, obj3, obj4};
    for(auto it = objects.begin(); it != objects.end(); ++it) {
        ASSERT_FALSE((*it)->GetParent());
        ASSERT_TRUE((*it)->GetChildren().empty());
    }
}

TEST(Object, Clone) {
    World world;
    Object_ptr original = world.CreateObject();
    original->SetPosition(glm::vec3(1, 2, 3));

    Object_ptr clone = original->Clone();

    // clone has different pointer address
    ASSERT_NE(original, clone);

    // clone has same member values as original
    ASSERT_EQ(clone->GetPosition(), glm::vec3(1, 2, 3));

    clone->SetPosition(glm::vec3(0));

    // original isn't altered when clone is
    ASSERT_NE(clone->GetPosition(), original->GetPosition());

    // add two children to original
    for (uint i = 0; i < 2; i++) {
        original->AddChild(world.CreateObject());
    }
    // new clone of original with children WITHOUT recursion
    clone = original->Clone(false);

    // without recursion a clone does not have any children
    ASSERT_TRUE(clone->GetChildren().empty());

    // new clone of original with children WITH recursion
    clone = original->Clone(true);

    // clone has same amount of children as original
    auto& originalChildren = original->GetChildren();
    auto& cloneChildren = clone->GetChildren();
    ASSERT_EQ(originalChildren.size(), cloneChildren.size());

    // cloned children are unique 
    for (uint i = 0; i < originalChildren.size(); i++) {
        ASSERT_NE(originalChildren[i], cloneChildren[i]);
    }
}

// class ForwardMessage : public Message {
//     public:
//         virtual void Test() const { };
//         virtual void Execute(Object& object) const override {
//             // call mocked test function
//             Test();
            
//             Object_ptr parent = object.GetParent();

//             // recurse on parent
//             if (parent) {
//                 parent->SendMessage(*this);
//             }
//         }
//         virtual ~ForwardMessage() {};
// };

// class MockForwardMessage : public ForwardMessage {
//     public:
//         MOCK_CONST_METHOD0(Test, void());
// };

// TEST(Message, Execute) {
//     World world;
//     Object_ptr object1 = world.CreateObject();
//     MockForwardMessage msg;

//     // test is only called once
//     EXPECT_CALL(msg, Test());
//     object1->SendMessage(msg);

//     Object_ptr object2 = world.CreateObject();
//     object2->AddChild(object1);

//     // test is called from both object1 and object2
//     EXPECT_CALL(msg, Test()).Times(2);
//     object1->SendMessage(msg);
// }
