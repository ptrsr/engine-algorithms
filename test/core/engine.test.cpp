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
        RemovedEntity(bool& on_removal)
            : on_removal(on_removal) 
            { }

        bool& on_removal;

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
        ASSERT_EQ(mock_entity.testnr, 1);
    }

    TEST(Engine, GetEntity) {
        Engine engine = Engine();

        // MockEntity does not exist yet, GetEntity returns empty optional
        ASSERT_FALSE(engine.GetEntity<MockEntity>().has_value());

        { // GetEntity returns an optional with a reference_wrapper for mock_entity
            MockEntity& mock_entity = engine.AddEntity<MockEntity>();

            auto mock_wrapper = engine.GetEntity<MockEntity>();
            ASSERT_TRUE(mock_wrapper.has_value());

            // both references point to the same MockEntity
            MockEntity& mock_ref = mock_wrapper->get();
            ASSERT_EQ(&mock_entity, &mock_ref);

            // GetEntity without index is the same as index 0
            ASSERT_EQ(&mock_entity, &engine.GetEntity<MockEntity>(0)->get());

            // index 1 is empty
            ASSERT_FALSE(engine.GetEntity<MockEntity>(1).has_value());
        }
        { // adding new entity results in index 1 having a value
            MockEntity& mock_entity = engine.AddEntity<MockEntity>();

            auto mock_wrapper = engine.GetEntity<MockEntity>(1);
            ASSERT_TRUE(mock_wrapper.has_value());

            // both references point to the same MockEntity
            MockEntity& mock_ref = mock_wrapper->get();
            ASSERT_EQ(&mock_entity, &mock_ref);
        }
    }

    TEST(Engine, GetEntities) {
        Engine engine = Engine();

        // no entities at init
        ASSERT_EQ(engine.GetEntities<MockEntity>().size(), 0);

        // add two entities
        MockEntity& ref0 = engine.AddEntity<MockEntity>();
        MockEntity& ref1 = engine.AddEntity<MockEntity>();

        // reference vector should contain 2 references
        auto test_entities = engine.GetEntities<MockEntity>();
        ASSERT_EQ(test_entities.size(), 2);

        // reference vector should contain correct references
        ASSERT_EQ(&test_entities[0].get(), &ref0);
        ASSERT_EQ(&test_entities[1].get(), &ref1);

        // no entities for EmptyEntity
        ASSERT_EQ(engine.GetEntities<EmtyEntity>().size(), 0);
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
        ASSERT_EQ(test_entities.size(), 0);

        // throw when trying to delete ref twice
        ASSERT_ANY_THROW(engine.DeleteEntity(mock_entity));

        // removed has been set to true on deletion of RemovedEntity
        ASSERT_TRUE(removed);
    }
}
