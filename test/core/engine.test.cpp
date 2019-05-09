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

class NullEntity : public Entity { };

TEST(Engine, AddEntity) {
    Engine engine = Engine();
    
    // add test entity
    TestEntity& testEntity = engine.AddEntity<TestEntity>(1);
    ASSERT_EQ(typeid(TestEntity), typeid(testEntity));
    ASSERT_EQ(testEntity.testnr, 1);
}

TEST(Engine, GetEntity) {
    Engine engine = Engine();

    // GetEntity should get same reference back to original entity
    TestEntity& ref0 = engine.AddEntity<TestEntity>();
    TestEntity& ref1 = engine.GetEntity<TestEntity>();
    ASSERT_EQ(&ref0, &ref1);

    // GetEntity with index should get right entity
    TestEntity& ref2 = engine.AddEntity<TestEntity>();
    TestEntity& ref3 = engine.GetEntity<TestEntity>(1);
    ASSERT_EQ(&ref2, &ref3);

    // cannot get nonexistent entity
    ASSERT_ANY_THROW(engine.GetEntity<NullEntity>());
}

TEST(Engine, GetEntities) {
    Engine engine = Engine();

    // add two entities
    TestEntity& ref0 = engine.AddEntity<TestEntity>();
    TestEntity& ref1 = engine.AddEntity<TestEntity>();

    // reference vector should contain 2 references
    auto test_entities = engine.GetEntities<TestEntity>();
    ASSERT_EQ(test_entities.size(), 2);

    // reference vector should contain correct references
    ASSERT_EQ(&test_entities[0].get(), &ref0);
    ASSERT_EQ(&test_entities[1].get(), &ref1);

    // cannot get nonexistent entities
    ASSERT_ANY_THROW(engine.GetEntities<NullEntity>());
}

TEST(Engine, DeleteEntity) {
    Engine engine = Engine();

    // create ref and delete it
    TestEntity& ref0 = engine.AddEntity<TestEntity>();
    engine.DeleteEntity(ref0);

    // list contains no more references
    auto test_entities = engine.GetEntities<TestEntity>();
    ASSERT_EQ(test_entities.size(), 0);

    // throw when trying to delete ref twice
    ASSERT_ANY_THROW(engine.DeleteEntity(ref0));
}
