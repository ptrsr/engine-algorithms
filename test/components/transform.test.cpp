#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <engine/components/transform.hpp>
#include <auxiliary/mat.aux.hpp>

#include <exception>
#include <iostream>

TEST(Transform, Init) {
    { // init with no parameters means unit mat4
        Transform transform = Transform();
        ASSERT_TRUE(CompareMats(glm::mat4(1), transform, 0.f));
    }
    {
        Transform transform = Transform(glm::mat4(2));
        ASSERT_TRUE(CompareMats(glm::mat4(2), transform, 0.f));
    }
}

TEST(Transform, Position) {
    Transform transform = Transform();

    // initial position is (0, 0, 0)
    ASSERT_EQ(glm::vec3(0, 0, 0), transform.GetPosition());

    // position is set
    transform.SetPosition(glm::vec3(1, 2, 3));
    ASSERT_EQ(glm::vec3(1, 2, 3), transform.GetPosition());

    // right column is set
    ASSERT_EQ(transform[3], glm::vec4(transform.GetPosition(), 1));
    
    // rest of matrix is not adjusted
    // (transpose because input is column major)
    ASSERT_TRUE(CompareMats(glm::transpose(glm::mat4(
         1,  0,  0,  1,
         0,  1,  0,  2,
         0,  0,  1,  3,
         0,  0,  0,  1
        )), transform, 0.f));
}

TEST(Transform, Translate) {
    Transform transform = Transform();

    // translating adds vector to position
    transform.Translate(glm::vec3(1, 2, 3));
    ASSERT_EQ(glm::vec3(1, 2, 3), transform.GetPosition());

    transform.Translate(glm::vec3(3, 2, 1));
    ASSERT_EQ(glm::vec3(4, 4, 4), transform.GetPosition());

    // rest of matrix is not adjusted
    // (transpose because input is column major)
    ASSERT_TRUE(CompareMats(glm::transpose(glm::mat4(
         1,  0,  0,  4,
         0,  1,  0,  4,
         0,  0,  1,  4,
         0,  0,  0,  1
    )), transform, 0.f));
}

TEST(Transform, rotation) {
    Transform transform = Transform();
    
    // new object should have identity matrix
    ASSERT_TRUE(CompareMats(glm::mat4(1), transform, TRIG_DIF));
    
    // rotating by pi should negate x and z vectors
    transform.Rotate(glm::pi<float>(), glm::vec3(0, 1, 0));
    ASSERT_TRUE(CompareMats(glm::mat4(
        -1,  0,  0,  0,
         0,  1,  0,  0,
         0,  0, -1,  0,
         0,  0,  0,  1
        ), transform, TRIG_DIF));

    // half a flip over X axis
    transform.Rotate(glm::pi<float>(), glm::vec3(1, 0, 0));

    // (no need to transpose, as it's a square matrix)
    ASSERT_TRUE(CompareMats(glm::mat4(
        -1,  0,  0,  0,
         0, -1,  0,  0,
         0,  0,  1,  0,
         0,  0,  0,  1
        ), transform, TRIG_DIF));
}



// TEST(Transform, Remove) {
//     World world;
//     Transform_ptr obj1 = world.CreateTransform();
//     Transform_ptr obj2 = world.CreateTransform();
//     Transform_ptr obj3 = world.CreateTransform();
//     Transform_ptr obj4 = world.CreateTransform();

//     // add two children to obj3
//     obj3->AddChild(obj1);
//     obj3->AddChild(obj2);

//     // parent obj4 to obj3
//     obj4->AddChild(obj3);
//     obj3->Remove();

//     // removed object has no more relations
//     ASSERT_TRUE(obj3->GetChildren().empty());
//     ASSERT_FALSE(obj3->GetParent());

//     // children moved to upper parent
//     ASSERT_EQ(obj1->GetParent(), obj4);
//     ASSERT_EQ(obj2->GetParent(), obj4);

//     // final parent has gained the two childeren
//     ASSERT_EQ(obj4->GetChildren().size(), 2);

//     // not able to remove (non recursively) without parent
//     ASSERT_THROW(obj4->Remove(), std::runtime_error);

//     // object is deleted after all pointers are lost
//     std::weak_ptr<Transform> weakptr = obj3;
//     obj3 = nullptr;
//     ASSERT_TRUE(weakptr.expired());

//     // recreate obj3
//     obj3 = world.CreateTransform();
//     obj3->AddChild(obj1);
//     obj3->AddChild(obj2);
//     obj4->AddChild(obj3);

//     // remove all
//     obj4->Remove(true);

//     // all (nested) childeren have no more parent and children
//     std::vector<Transform_ptr> objects = {obj1, obj2, obj3, obj4};
//     for(auto it = objects.begin(); it != objects.end(); ++it) {
//         ASSERT_FALSE((*it)->GetParent());
//         ASSERT_TRUE((*it)->GetChildren().empty());
//     }
// }

// TEST(Transform, Clone) {
//     World world;
//     Transform_ptr original = world.CreateTransform();
//     original->SetPosition(glm::vec3(1, 2, 3));

//     Transform_ptr clone = original->Clone();

//     // clone has different pointer address
//     ASSERT_NE(original, clone);

//     // clone has same member values as original
//     ASSERT_EQ(clone->GetPosition(), glm::vec3(1, 2, 3));

//     clone->SetPosition(glm::vec3(0));

//     // original isn't altered when clone is
//     ASSERT_NE(clone->GetPosition(), original->GetPosition());

//     // add two children to original
//     for (uint i = 0; i < 2; i++) {
//         original->AddChild(world.CreateTransform());
//     }
//     // new clone of original with children WITHOUT recursion
//     clone = original->Clone(false);

//     // without recursion a clone does not have any children
//     ASSERT_TRUE(clone->GetChildren().empty());

//     // new clone of original with children WITH recursion
//     clone = original->Clone(true);

//     // clone has same amount of children as original
//     auto& originalChildren = original->GetChildren();
//     auto& cloneChildren = clone->GetChildren();
//     ASSERT_EQ(originalChildren.size(), cloneChildren.size());

//     // cloned children are unique 
//     for (uint i = 0; i < originalChildren.size(); i++) {
//         ASSERT_NE(originalChildren[i], cloneChildren[i]);
//     }
// }

// class ForwardMessage : public Message {
//     public:
//         virtual void Test() const { };
//         virtual void Execute(Transform& object) const override {
//             // call mocked test function
//             Test();
            
//             Transform_ptr parent = object.GetParent();

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
//     Transform_ptr object1 = world.CreateTransform();
//     MockForwardMessage msg;

//     // test is only called once
//     EXPECT_CALL(msg, Test());
//     object1->SendMessage(msg);

//     Transform_ptr object2 = world.CreateTransform();
//     object2->AddChild(object1);

//     // test is called from both object1 and object2
//     EXPECT_CALL(msg, Test()).Times(2);
//     object1->SendMessage(msg);
// }
