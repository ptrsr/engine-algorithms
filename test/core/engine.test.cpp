#include <gtest/gtest.h>

#include <engine/core/engine.hpp>
#include <engine/core/entity.hpp>

#include <iostream>

namespace {
    class MockEntity : public Entity { 
    public:
        MockEntity(const int testnr = 0)
            : testnr(testnr) 
            { }

        int testnr;
    };

    class EmtyEntity : public Entity { };

    class RemovedEntity : public Entity {
    public:
        bool& on_removal;
        
        RemovedEntity(bool& on_removal)
            : on_removal(on_removal) 
            { }

    protected:
        ~RemovedEntity() {
            on_removal = true;
        }
    };

    TEST(Engine, AddEntity) {
        Engine engine = Engine();
        
        // add test entity and assert parameter forwarding
        MockEntity& mock_entity = engine.AddEntity<MockEntity>(1);
        ASSERT_EQ(typeid(MockEntity), typeid(mock_entity));
        ASSERT_EQ(1, mock_entity.testnr);
    }

    TEST(Engine, GetEntity) {
        Engine engine = Engine();

        // MockEntity does not exist yet, GetEntity returns empty optional
        ASSERT_FALSE(engine.GetEntity<MockEntity>());

        { // GetEntity returns an optional with a reference_wrapper for mock_entity
            MockEntity& mock_entity = engine.AddEntity<MockEntity>();

            MockEntity* const mock_ptr = engine.GetEntity<MockEntity>();
            ASSERT_TRUE(mock_ptr);

            // both references point to the same MockEntity
            ASSERT_EQ(&mock_entity, mock_ptr);

            // GetEntity without index is the same as index 0
            ASSERT_EQ(&mock_entity, engine.GetEntity<MockEntity>(0));

            // index 1 is empty
            ASSERT_FALSE(engine.GetEntity<MockEntity>(1));
        }
        { // adding new entity results in index 1 having a value
            MockEntity& mock_entity = engine.AddEntity<MockEntity>();

            MockEntity* const mock_ptr = engine.GetEntity<MockEntity>(1);
            ASSERT_TRUE(mock_ptr);

            // both references point to the same MockEntity
            ASSERT_EQ(&mock_entity, mock_ptr);
        }
    }

    TEST(Engine, GetEntities) {
        Engine engine = Engine();

        // no entities at init
        ASSERT_EQ(0, engine.GetEntities<MockEntity>().size());

        // add two entities
        MockEntity& ref0 = engine.AddEntity<MockEntity>();
        MockEntity& ref1 = engine.AddEntity<MockEntity>();

        // reference vector should contain 2 references
        auto test_entities = engine.GetEntities<MockEntity>();
        ASSERT_EQ(2, test_entities.size());

        // reference vector should contain correct references
        ASSERT_EQ(&ref0, &test_entities[0].get());
        ASSERT_EQ(&ref1, &test_entities[1].get());

        // no entities for EmptyEntity
        ASSERT_EQ(0, engine.GetEntities<EmtyEntity>().size());
    }

    TEST(Engine, DeleteEntity) {
        Engine engine = Engine();

        bool removed = false;

        // create a RemovedEntity
        RemovedEntity& mock_entity = engine.AddEntity<RemovedEntity>(removed);

        { // other engine (with no knowledge of mock_entity) throws on wrong removal
            Engine tmp_engine = Engine();
            ASSERT_ANY_THROW(tmp_engine.DeleteEntity(mock_entity));
        }
        // delete mock_entity
        engine.DeleteEntity(mock_entity);

        // list contains no more references
        auto test_entities = engine.GetEntities<RemovedEntity>();
        ASSERT_EQ(0, test_entities.size());

        // throw when trying to delete ref twice
        ASSERT_ANY_THROW(engine.DeleteEntity(mock_entity));

        // removed has been set to true on deletion of RemovedEntity
        ASSERT_TRUE(removed);
    }

    TEST(Engine, CloneEntity) {
        Engine engine = Engine();

        MockEntity& mock_entity = engine.AddEntity<MockEntity>(123);
        MockEntity& clone_entity = engine.CloneEntity(mock_entity);

        // cloned entity has different address
        ASSERT_NE(&mock_entity, &clone_entity);

        // cloned entity has same field values however
        ASSERT_EQ(mock_entity.testnr, clone_entity.testnr);

        // clone has been added to engine
        ASSERT_EQ(2, engine.GetEntities<MockEntity>().size());

        // correct address of clone has been added 
        ASSERT_EQ(&clone_entity, engine.GetEntity<MockEntity>(1));
    }
}
