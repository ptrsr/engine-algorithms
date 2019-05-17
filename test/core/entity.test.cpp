#include <gtest/gtest.h>

#include <engine/core/engine.hpp>

namespace {
    // test component with field
    class MockComponent : public Component {
    public:
        MockComponent(int test_int)
            : test_int(test_int) 
            { }
            
        virtual Component* Clone() override {
            return new MockComponent(*this);
        }

        int test_int;
    };

    // test entity class that adds a MockComponent
    class MockEntity : public Entity { 
    public:
        MockEntity(int test_int = 0)
            : mock_component(AddComponent<MockComponent>(test_int))
            , test_component(AddComponent<MockComponent>(0))
            { }
        
        MockComponent& mock_component;
        MockComponent& test_component;
    };

    // test entity to check non existance of component
    class NullComponent : public Component { };

    TEST(Entity, AddComponent) {
        Engine engine = Engine();

        // forwarding arguments to component constructor
        MockEntity& mock_entity = engine.AddEntity<MockEntity>(1);
        ASSERT_EQ(1, mock_entity.mock_component.test_int);

        /* each entity can only have one component of a single type.
        adding another one returns a reference to the original.*/
        ASSERT_EQ(&mock_entity.mock_component, &mock_entity.test_component);

        // the second (ignored) addition does not change the original component
        ASSERT_EQ(1, mock_entity.test_component.test_int);
    }

    TEST(Entity, GetComponent) {
        Engine engine = Engine();
        MockEntity& mock_entity = engine.AddEntity<MockEntity>();

        // MockEntity has no NullComponent, returns empty optional
        ASSERT_FALSE(mock_entity.GetComponent<NullComponent>());

        MockComponent* const component_ptr = mock_entity.GetComponent<MockComponent>();

        // MockEntity has MockComponent, same as the added field
        ASSERT_TRUE(component_ptr);
        ASSERT_EQ(&mock_entity.mock_component, component_ptr);
    }
}
