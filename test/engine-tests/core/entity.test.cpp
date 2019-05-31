#include <gtest/gtest.h>

#include <engine/core/entity.hpp>

/* NOTE: since Entity is based on TypeMap, most functionality will be tested
   in typemap.test.cpp . here we will test the possiblities of multi inheritance
   for entities. */

namespace {
    class MockComponent : public Component {
    public:
        MockComponent(Entity* entity)
            : Component(entity)
            { }
            
        virtual Component* Clone() override {
            return new MockComponent(*this);
        }
    };

    class MockEntityA : virtual public Entity { 
    public:
        MockEntityA()
            : mock_component_a(AddComponent<MockComponent>())
            { }
        
        MockComponent& mock_component_a;
    };

    class MockEntityB : virtual public Entity { 
    public:
        MockEntityB()
            : mock_component_b(AddComponent<MockComponent>())
            { }
        
        MockComponent& mock_component_b;
    };

    class MockEntityC : public MockEntityA, public MockEntityB { };

    TEST(EntityTest, MultiBase) {
        MockEntityC test_entity = MockEntityC();

        // MockEntityC's MockComponents point to the same MockComponent
        ASSERT_EQ(&test_entity.mock_component_a, &test_entity.mock_component_b);
    }
}
