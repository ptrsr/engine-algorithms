#include <gtest/gtest.h>

#include <engine/core/entity.hpp>

/* NOTE: since Entity is based on TypeMap, most functionality will be tested
   in typemap.test.cpp . here we will test the possiblities of multi inheritance
   for entities. */

namespace {
    class MockComponent : public Component {
    public:
        MockComponent(Entity* entity, int test_int)
            : Component(entity)
            , test_int(test_int) 
            { }
            
        virtual Component* Clone() override {
            return new MockComponent(*this);
        }

        int test_int;
    };

    class MockEntityA : virtual public Entity { 
    public:
        MockEntityA(int test_int = 0)
            : mock_component_a(AddComponent<MockComponent>(test_int))
            { }
        
        MockComponent& mock_component_a;
    };

    class MockEntityB : virtual public Entity { 
    public:
        MockEntityB(int test_int = 0)
            : mock_component_b(AddComponent<MockComponent>(test_int))
            { }
        
        MockComponent& mock_component_b;
    };

    class MockEntityC : public MockEntityA, public MockEntityB { };

    TEST(Entity, MultiBase) {
        MockEntityC test_entity = MockEntityC();
        ASSERT_EQ(&test_entity.mock_component_a, &test_entity.mock_component_b);
    }
}
