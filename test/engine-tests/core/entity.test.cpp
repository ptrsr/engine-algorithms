#include <gtest/gtest.h>

#include <engine/core/scene.hpp>
#include <engine/core/entity.hpp>

/* NOTE: since Entity is based on TypeMap, most functionality will be tested
   in typemap.test.cpp . */
namespace {
    // same MockComponent as in component.test
    class MockComponent : public Component {
    public:
        const int data;

        MockComponent(Entity* const entity = nullptr, const int data = 0)
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

        /* constructor that takes a smart pointer to a component.
           this is for shared components */
        // MockEntity(const unsigned id, MockComponent_ptr mock_component)
        //     : Entity(id)
        //     , mock_component(AddComponent(mock_component))
        //     { }
    };

    TEST(EntityTest, Constructor) {
        {
            MockEntity entity;
            ASSERT_EQ(0, entity.id);
            ASSERT_EQ(0, entity.mock_component.data);

            // Entity owning Component is given to Component
            ASSERT_EQ(&entity, entity.mock_component.entity);

        }
        {
            MockEntity entity(1, 1);
            ASSERT_EQ(1, entity.id);

            // data is properly forwarded through AddComponent
            ASSERT_EQ(1, entity.mock_component.data);

            // forwarding data does not influence Entity pass to Component
            ASSERT_EQ(&entity, entity.mock_component.entity);
        }
    }

    TEST(EntityTest, AddComponent) {
        MockEntity entity;

        MockComponent& original = entity.mock_component;

        // MockComponent has already been added, returning reference to original
        MockComponent& component = entity.AddComponent<MockComponent>();

        ASSERT_EQ(&original, &component);
    }

    TEST(EntityTest, GetComponent) {
        MockEntity entity;
        Entity* base = (Entity*)&entity;

        MockComponent* component = base->GetComponent<MockComponent>();

        // GetComponent returns pointer to added Component through base class
        ASSERT_EQ(&entity.mock_component, component);

        // GetComponent returns nullptr when Entity does not contain derived type of Component
        ASSERT_FALSE(entity.GetComponent<NullComponent>());
    }
}
