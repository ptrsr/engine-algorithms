#include <gtest/gtest.h>

#include <engine/core/scene.hpp>

namespace {
    // scene test setup
    class SceneTest : public ::testing::Test {
    protected:
        Scene scene;
    };

    class MockEntity : public Entity { 
    public:
        MockEntity(const unsigned int id = 0, const int testnr = 0)
            : Entity(id)
            , testnr(testnr) 
            { }

        MockEntity(const unsigned int id, const MockEntity& original)
            : Entity(id)
            , testnr(original.testnr)
            { }

        int testnr;
    };

    class EmtyEntity : public Entity { };

    class RemovedEntity : public Entity {
    public:
        bool& on_removal;
        
        RemovedEntity(const unsigned int id, bool& on_removal)
            : Entity(id)
            , on_removal(on_removal) 
            { }

        ~RemovedEntity() {
            on_removal = true;
        }
    };

    class BaseEntity : public Entity {
        // forward constructor to Entity
        using Entity::Entity;
    };

    class DerivedEntity : public BaseEntity {
        // example of constructor linking
        using BaseEntity::BaseEntity;
    };

    TEST_F(SceneTest, AddEntity) {
        {
            // add test entity and assert parameter forwarding
            MockEntity& mock_entity = scene.AddEntity<MockEntity>(1);
            ASSERT_EQ(typeid(MockEntity), typeid(mock_entity));
            ASSERT_EQ(1, mock_entity.id);

            // first entity added to scene has ID of 1
            ASSERT_EQ(1, mock_entity.testnr);
        }
        { // test if AddEntity works without parameters
            MockEntity& mock_entity = scene.AddEntity<MockEntity>();
            ASSERT_EQ(0, mock_entity.testnr);

            // each entity gets a unique ID that increments
            ASSERT_EQ(2, mock_entity.id);
        }
        { // not forwarding id results in id of 0 (null)
            EmtyEntity empty_entity;
            ASSERT_EQ(0, empty_entity.id);
        }
    }

    TEST_F(SceneTest, GetEntity) {
        // MockEntity does not exist yet, GetEntity returns empty optional
        ASSERT_FALSE(scene.GetEntity<MockEntity>());

        { // GetEntity returns an optional with a reference_wrapper for mock_entity
            MockEntity& mock_entity = scene.AddEntity<MockEntity>();

            MockEntity* const mock_ptr = scene.GetEntity<MockEntity>();
            ASSERT_TRUE(mock_ptr);

            // both references point to the same MockEntity
            ASSERT_EQ(&mock_entity, mock_ptr);

            // GetEntity without index is the same as index 0
            ASSERT_EQ(&mock_entity, scene.GetEntity<MockEntity>(0));

            // index 1 is empty
            ASSERT_FALSE(scene.GetEntity<MockEntity>(1));
        }
        { // adding new entity results in index 1 having a value
            MockEntity& mock_entity = scene.AddEntity<MockEntity>();

            MockEntity* const mock_ptr = scene.GetEntity<MockEntity>(1);
            ASSERT_TRUE(mock_ptr);

            // both references point to the same MockEntity
            ASSERT_EQ(&mock_entity, mock_ptr);
        }
    }

    TEST_F(SceneTest, GetEntities) {
        // no entities at init
        ASSERT_EQ(0, scene.GetEntities<MockEntity>().size());

        // add two entities
        MockEntity& ref0 = scene.AddEntity<MockEntity>();
        MockEntity& ref1 = scene.AddEntity<MockEntity>();

        // reference vector should contain 2 references
        auto test_entities = scene.GetEntities<MockEntity>();
        ASSERT_EQ(2, test_entities.size());

        // reference vector should contain correct references
        ASSERT_EQ(&ref0, test_entities[0]);
        ASSERT_EQ(&ref1, test_entities[1]);

        // no entities for EmptyEntity
        ASSERT_EQ(0, scene.GetEntities<EmtyEntity>().size());
    }

    TEST_F(SceneTest, DeleteEntity) {
        bool removed = false;

        // create a RemovedEntity
        RemovedEntity& mock_entity = scene.AddEntity<RemovedEntity>(removed);

        { // other scene (with no knowledge of mock_entity) throws on wrong removal
            Scene tmp_scene = Scene();
            ASSERT_ANY_THROW(tmp_scene.DeleteEntity(mock_entity));
        }
        // delete mock_entity
        scene.DeleteEntity(mock_entity);

        // list contains no more references
        auto test_entities = scene.GetEntities<RemovedEntity>();
        ASSERT_EQ(0, test_entities.size());

        // throw when trying to delete ref twice
        ASSERT_ANY_THROW(scene.DeleteEntity(mock_entity));

        // removed has been set to true on deletion of RemovedEntity
        ASSERT_TRUE(removed);
    }

    TEST_F(SceneTest, CloneEntity) {
        MockEntity& mock_entity = scene.AddEntity<MockEntity>(123);
        MockEntity& clone_entity = scene.CloneEntity(mock_entity);

        // cloned entity has different address
        ASSERT_NE(&mock_entity, &clone_entity);

        // cloned entity has incremented id
        ASSERT_EQ(1, mock_entity.id);
        ASSERT_EQ(2, clone_entity.id);

        // cloned entity has same field values however
        ASSERT_EQ(mock_entity.testnr, clone_entity.testnr);

        // clone has been added to scene
        ASSERT_EQ(2, scene.GetEntities<MockEntity>().size());

        // correct address of clone has been added 
        ASSERT_EQ(&clone_entity, scene.GetEntity<MockEntity>(1));
    }

    TEST_F(SceneTest, RegisterEntity) {
        DerivedEntity& derived_ref = scene.AddEntity<DerivedEntity>();
        scene.RegisterEntity<BaseEntity>(derived_ref);
        BaseEntity* base_ptr = scene.GetEntity<BaseEntity>();

        // new shared pointer to base class has same adress
        ASSERT_EQ(&derived_ref, base_ptr);
    }
}
