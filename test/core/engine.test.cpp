#include <gtest/gtest.h>

#include <engine/core/engine.hpp>
#include <engine/core/entity.hpp>

#include <iostream>

class MockEntity : public Entity { 
    public:
        MockEntity(const int testnr = 0)
            : testnr(testnr) { }

        int testnr;

};

class EmtyEntity : public Entity { };

TEST(Engine, AddEntity) {
    Engine engine = Engine();
    
    // add test entity
    MockEntity& testEntity = engine.AddEntity<MockEntity>(1);
    ASSERT_EQ(typeid(MockEntity), typeid(testEntity));
    ASSERT_EQ(testEntity.testnr, 1);
}

TEST(Engine, CheckEntity) {
    Engine engine = Engine();

    // CheckEntity returns true after adding Entity
    ASSERT_FALSE(engine.CheckEntity<MockEntity>());
    MockEntity& testEntity = engine.AddEntity<MockEntity>();
    ASSERT_TRUE(engine.CheckEntity<MockEntity>());

    // CheckEntity checks index
    ASSERT_FALSE(engine.CheckEntity<EmtyEntity>());
    EmtyEntity& null_entity0 = engine.AddEntity<EmtyEntity>();
    ASSERT_FALSE(engine.CheckEntity<EmtyEntity>(1));
    EmtyEntity& null_entity1 = engine.AddEntity<EmtyEntity>();
    ASSERT_TRUE(engine.CheckEntity<EmtyEntity>(1));
}

TEST(Engine, GetEntity) {
    Engine engine = Engine();

    // GetEntity should get same reference back to original entity
    MockEntity& ref0 = engine.AddEntity<MockEntity>();
    MockEntity& ref1 = engine.GetEntity<MockEntity>();
    ASSERT_EQ(&ref0, &ref1);

    // GetEntity with index should get right entity
    MockEntity& ref2 = engine.AddEntity<MockEntity>();
    MockEntity& ref3 = engine.GetEntity<MockEntity>(1);
    ASSERT_EQ(&ref2, &ref3);

    // cannot get nonexistent entity
    ASSERT_ANY_THROW(engine.GetEntity<EmtyEntity>());
}

TEST(Engine, GetEntities) {
    Engine engine = Engine();

    // add two entities
    MockEntity& ref0 = engine.AddEntity<MockEntity>();
    MockEntity& ref1 = engine.AddEntity<MockEntity>();

    // reference vector should contain 2 references
    auto test_entities = engine.GetEntities<MockEntity>();
    ASSERT_EQ(test_entities.size(), 2);

    // reference vector should contain correct references
    ASSERT_EQ(&test_entities[0].get(), &ref0);
    ASSERT_EQ(&test_entities[1].get(), &ref1);

    // cannot get nonexistent entities
    ASSERT_ANY_THROW(engine.GetEntities<EmtyEntity>());
}

TEST(Engine, DeleteEntity) {
    Engine engine = Engine();

    // create ref and delete it
    MockEntity& ref0 = engine.AddEntity<MockEntity>();
    engine.DeleteEntity(ref0);

    // list contains no more references
    auto test_entities = engine.GetEntities<MockEntity>();
    ASSERT_EQ(test_entities.size(), 0);

    // throw when trying to delete ref twice
    ASSERT_ANY_THROW(engine.DeleteEntity(ref0));
}
