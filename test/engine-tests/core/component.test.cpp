#include <gtest/gtest.h>

#include <engine/core/scene.hpp>
#include <engine/core/component.hpp>
#include <engine/core/entity.hpp>

#include <iostream>

namespace {
    class MockComponent : public Component {
    private:
        bool& on_removal;

    public:
        MockComponent(bool& on_removal, Entity* const entity)
            : Component(entity)
            , on_removal(on_removal)
            { }

        MockComponent(MockComponent& original)
            : Component(original.entity)
            , on_removal(original.on_removal)
            { }

        ~MockComponent() {
            on_removal = true;
        }

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
        Scene scene = Scene();
        bool removed = false;

        MockEntity& entity = scene.AddEntity<MockEntity>(removed);
        
        // removed equals true after calling destructor of MockEntity
        scene.DeleteEntity(entity);
        ASSERT_TRUE(removed);
    }

    TEST(ComponentTest, Clone) {
        Scene scene = Scene();
        bool removed = false;

        MockEntity& original = scene.AddEntity<MockEntity>(removed);
        MockEntity& copy = scene.CloneEntity(original);

        ASSERT_NE(&original.mock_component, &copy.mock_component);
    }
}
