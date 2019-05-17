#include <gtest/gtest.h>

#include <engine/core/engine.hpp>
#include <iostream>

namespace {
    class MockComponent : public Component {
    private:
        ~MockComponent() {
            on_removal = true;
        }

        bool& on_removal;

    public:
        MockComponent(bool& on_removal)
            : on_removal(on_removal)
            { }

        virtual Component* Clone() override {
            return new MockComponent(*this);
        }
    };

    class MockEntity : public Entity {
    public:
        MockComponent& mock_component;

        MockEntity(bool& on_removal)
            : mock_component(AddComponent<MockComponent>(on_removal)) 
            { }

        MockEntity(const MockEntity& mock_entity)
            : mock_component(mock_entity.mock_component)
            { }
    };

    TEST(Component, Destructor) {
        Engine engine = Engine();
        bool removed = false;

        MockEntity& entity = engine.AddEntity<MockEntity>(removed);
        
        // removed equals true after calling destructor of MockEntity
        engine.DeleteEntity(entity);
        ASSERT_TRUE(removed);
    }

    TEST(Component, Clone) {
        Engine engine = Engine();
        bool removed = false;

        MockEntity& original = engine.AddEntity<MockEntity>(removed);
        MockEntity& copy = engine.CloneEntity(original);

        ASSERT_NE(&original.mock_component, &copy.mock_component);
    }
}
