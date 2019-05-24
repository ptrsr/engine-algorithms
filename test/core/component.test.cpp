#include <gtest/gtest.h>

#include <engine/core/engine.hpp>
#include <engine/core/component.hpp>
#include <engine/core/entity.hpp>

#include <iostream>

namespace {
    class MockComponent : public Component {
    private:
        ~MockComponent() {
            on_removal = true;
        }
        
        bool& on_removal;

    public:
        MockComponent(Entity* const entity, bool& on_removal)
            : Component(entity)
            , on_removal(on_removal)
            { }

        MockComponent(MockComponent& original)
            : Component(original.entity)
            , on_removal(original.on_removal)
            { }

        virtual Component* Clone() override {
            return new MockComponent(*this);
        }
    };

    class MockEntity : public Entity {
    public:
        MockComponent& mock_component;

        MockEntity(const unsigned int id, bool& on_removal)
            : Entity(id)
            , mock_component(AddComponent<MockComponent>(on_removal)) 
            { }

        MockEntity(const unsigned int id, MockEntity& original)
            : Entity(id) 
            , mock_component(*GetComponent<MockComponent>())
            { }

    };

    TEST(ComponentTest, Destructor) {
        Engine engine = Engine();
        bool removed = false;

        MockEntity& entity = engine.AddEntity<MockEntity>(removed);
        
        // removed equals true after calling destructor of MockEntity
        engine.DeleteEntity(entity);
        ASSERT_TRUE(removed);
    }

    TEST(ComponentTest, Clone) {
        Engine engine = Engine();
        bool removed = false;

        MockEntity& original = engine.AddEntity<MockEntity>(removed);
        MockEntity& copy = engine.CloneEntity(original);

        ASSERT_NE(&original.mock_component, &copy.mock_component);
    }
}
