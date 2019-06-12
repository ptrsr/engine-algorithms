#include <gtest/gtest.h>

#include <engine/core/scene.hpp>


namespace {
    class MockComponent : public Component {
    public:
        const int data;

        // default constructor of mock
        MockComponent(Entity* const entity = nullptr, const int data = 0)
            : Component(entity)
            , data(data)
            { }

        // copy constructor of mock
        MockComponent(MockComponent& copy, Entity* const entity)
            : Component(entity)
            , data(copy.data)
            { }

        // simple clone function
        virtual Component_ptr Clone(Entity* const entity) override {
            /* copy is a shorthand for creating a new Component_ptr 
               of <component-type> */
            return Copy<MockComponent>(*this, entity);
        }
    };

    TEST(ComponentTest, Clone) {
        {
            // default data with 0
            MockComponent component;
            ASSERT_EQ(0, component.data);
        }
        // init with entity and data
        Entity entity_A;
        MockComponent component(&entity_A, 1);
        ASSERT_EQ(&entity_A, component.entity);
        ASSERT_EQ(1, component.data);

        // clone component with data but other entity
        Entity entity_B;
        Component_ptr clone = component.Clone(&entity_B);
        ASSERT_EQ(&entity_B, clone->entity);
        ASSERT_EQ(1, static_cast<MockComponent*>(clone.get())->data);
    }
}

namespace {
    class MockSharedComponent : public SharedComponent {
    public:
        using SharedComponent::SharedComponent;

        // example clone function of SharedComponent
        Component_ptr Clone(Entity* const original) override {
            return shared_from_this();
        }
    };

    class MockEntity : public Entity {
    public:
        MockSharedComponent& shared_component;
        
        // default constructor
        MockEntity(const unsigned id, std::shared_ptr<MockSharedComponent>& shared_component)
            : Entity(id)
            , shared_component(AddComponent(shared_component))
            { }

        // copy constructor
        MockEntity(const Entity& original, const unsigned id)
            : Entity(original, id)
            , shared_component(*GetComponent<MockSharedComponent>())
            { }
    };

    TEST(SharedComponentTest, Clone) {
        Scene scene;
        std::shared_ptr<MockSharedComponent> component = std::make_shared<MockSharedComponent>();

        MockEntity& entity = scene.AddEntity<MockEntity>(component);

        // both Entities have the same Component
        ASSERT_EQ(component.get(), &scene.GetEntity<MockEntity>()->shared_component);

        // cloning through scene results in new entity with same SharedComponent
        MockEntity& copy = scene.CloneEntity(entity);
        ASSERT_EQ(component.get(), &entity.shared_component);
    }
}
