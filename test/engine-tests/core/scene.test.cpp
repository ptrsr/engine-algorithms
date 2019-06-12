#include <gtest/gtest.h>

#include <engine/core/scene.hpp>

namespace {
    class SceneTest : public ::testing::Test {
    protected:
        Scene scene;
    };

    class MockComponent : public Component {
    public:
        const int data;
        bool* removed = nullptr;

        MockComponent(Entity* const entity, const int data = 0)
            : Component(entity)
            , data(data)
            { }

        MockComponent(MockComponent& copy, Entity* const entity)
            : Component(entity)
            , data(copy.data)
            { }

        virtual Component_ptr Clone(Entity* const entity) override {
            return Copy<MockComponent>(*this, entity);
        }

        ~MockComponent() {
            if (removed) {
                *removed = true;
            }
        }
    };

    class NullComponent : public Component { };

    class MockEntity : public Entity {
    public:
        MockComponent& mock_component;

        /* constructor that instantiates a new component
           with forwarded data */
        MockEntity(const unsigned id = 0, const int data = 0)
            : Entity(id)
            , mock_component(AddComponent<MockComponent>(data))
            { }


        /* a copy constructor. Component copying is handled
           by the base Entity copy constructor */
        MockEntity(const Entity& original, const unsigned id)
            : Entity(original, id)
            , mock_component(*GetComponent<MockComponent>())
            { }
    };

    class DerivedEntity : public MockEntity { 
        /* useful forwarding of base constructors. this is also
           possible for components */
        using MockEntity::MockEntity;
    };


    TEST_F(SceneTest, AddEntity) {
        {
            auto& entity = scene.AddEntity<MockEntity>();
            ASSERT_EQ(typeid(MockEntity), typeid(entity));

            // first entity added to scene has id of 1
            ASSERT_EQ(1, entity.id);

            // used default data
            ASSERT_EQ(0, entity.mock_component.data);
        }
        { // test data forwarding through AddEntity
            MockEntity& entity = scene.AddEntity<MockEntity>(1);

            // id incremented on adding new Entity
            ASSERT_EQ(2, entity.id);

            // data forwarded correctly
            ASSERT_EQ(1, entity.mock_component.data);
        }
    }

    TEST_F(SceneTest, GetEntity) {
        // MockEntity does not exist yet, return nullptr
        ASSERT_FALSE(scene.GetEntity<MockEntity>());

        { // GetEntity returns an optional with a reference_wrapper for entity
            MockEntity& entity = scene.AddEntity<MockEntity>();

            MockEntity* const mock_ptr = scene.GetEntity<MockEntity>();
            ASSERT_TRUE(mock_ptr);

            // both references point to the same MockEntity
            ASSERT_EQ(&entity, mock_ptr);

            // GetEntity without index is the same as index 0
            ASSERT_EQ(&entity, scene.GetEntity<MockEntity>(0));

            // index 1 is empty
            ASSERT_FALSE(scene.GetEntity<MockEntity>(1));
        }
        { // adding new entity results in index 1 having a value
            MockEntity& entity = scene.AddEntity<MockEntity>(1);

            MockEntity* const mock_ptr = scene.GetEntity<MockEntity>(1);
            
            // returned a valid pointer and new MockEntity has correct data
            ASSERT_TRUE(mock_ptr);
            ASSERT_EQ(1, entity.mock_component.data);

            // both references point to the same MockEntity
            ASSERT_EQ(&entity, mock_ptr);
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
        ASSERT_EQ(0, scene.GetEntities<DerivedEntity>().size());
    }

    TEST_F(SceneTest, CloneEntity) {
        MockEntity& entity = scene.AddEntity<MockEntity>(123);
        MockEntity& clone = scene.CloneEntity(entity);

        // cloned Entity and it's Components are completely new
        ASSERT_NE(&entity, &clone);
        ASSERT_NE(&entity.mock_component, &clone.mock_component);

        // cloned entity has incremented id
        ASSERT_EQ(1, entity.id);
        ASSERT_EQ(2, clone.id);

        // cloned entity has same field values however
        ASSERT_EQ(entity.mock_component.data, clone.mock_component.data);

        // clone has been added to scene
        ASSERT_EQ(2, scene.GetEntities<MockEntity>().size());

        // correct address of clone has been added 
        ASSERT_EQ(&clone, scene.GetEntity<MockEntity>(1));
    }

    TEST_F(SceneTest, RegisterEntity) {
        DerivedEntity& entity = scene.AddEntity<DerivedEntity>();

        // no MockEntity exists yet
        ASSERT_FALSE(scene.GetEntity<MockEntity>());

        // register on base class succesful
        ASSERT_TRUE(scene.RegisterEntity<MockEntity>(entity));

        // cannot register twice, return false
        ASSERT_FALSE(scene.RegisterEntity<MockEntity>(entity));

        /* derived class exists once but has been registered twice, 
           resulting in the same adress */
        MockEntity* base = scene.GetEntity<MockEntity>();
        ASSERT_EQ(&entity, base);

        // throw when registering entity that has never been added to scene
        {
            DerivedEntity derived;
            ASSERT_ANY_THROW(scene.RegisterEntity<MockEntity>(derived));
        }
    }

    TEST_F(SceneTest, DeleteEntity) {
        bool removed = false;

        DerivedEntity& entity = scene.AddEntity<DerivedEntity>();
        scene.RegisterEntity<MockEntity>(entity);
        entity.mock_component.removed = &removed;

        { // other scene (with no knowledge of entity) throws on wrong removal
            Scene tmp_scene;
            ASSERT_ANY_THROW(tmp_scene.DeleteEntity(entity));
        }

        // delete entity
        scene.DeleteEntity(entity);

        // all registered versions are removed
        ASSERT_FALSE(scene.GetEntity<MockEntity>());
        ASSERT_FALSE(scene.GetEntity<DerivedEntity>());

        /* when Entity is removed, so will it's Components.
           the MockComponent destructor sets removed to true */
        ASSERT_TRUE(removed);

        // throw when trying to delete ref twice
        ASSERT_ANY_THROW(scene.DeleteEntity(entity));
    }

    TEST_F(SceneTest, UnRegister) {
        bool removed = false;

        DerivedEntity& entity = scene.AddEntity<DerivedEntity>();
        scene.RegisterEntity<MockEntity>(entity);
        entity.mock_component.removed = &removed;

        scene.UnRegisterEntity<DerivedEntity>(entity);
        ASSERT_FALSE(scene.GetEntity<DerivedEntity>());
        
        // removed is still false since Entity still exists as MockEntity
        ASSERT_FALSE(removed);

        // removing all registered versions results in deletion of Entity
        scene.UnRegisterEntity<MockEntity>(entity);
        ASSERT_TRUE(removed);
    }
}
