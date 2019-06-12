#include <gtest/gtest.h>

#include <engine/core/entity.hpp>


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
