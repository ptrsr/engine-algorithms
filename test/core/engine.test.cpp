#include <gtest/gtest.h>

#include <engine/core/engine.hpp>
#include <engine/core/entity.hpp>

#include <iostream>

class TestEntity : public Entity { 
    public:
        TestEntity(const int testnr = 0)
            : testnr(testnr) { }

        int testnr;

};

TEST(Engine, AddEntity) {
    Engine engine = Engine();
    
    // add test entity
    TestEntity& testEntity = engine.AddEntity<TestEntity>(1);
    EXPECT_EQ(typeid(TestEntity), typeid(testEntity));
    EXPECT_EQ(testEntity.testnr, 1);
}

TEST(Engine, GetEntity) {
    Engine engine = Engine();

    TestEntity& ref1 = engine.AddEntity<TestEntity>();
    TestEntity& ref2 = engine.GetEntity<TestEntity>();
    // GetEntity should get same reference back to original entity
    EXPECT_EQ(&ref1, &ref2);

    TestEntity& ref3 = engine.AddEntity<TestEntity>();
    TestEntity& ref4 = engine.GetEntity<TestEntity>(1);
    // GetEntity with index should get right entity
    EXPECT_EQ(&ref3, &ref4);
}
