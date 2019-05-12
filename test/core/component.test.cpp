#include <gtest/gtest.h>

#include <engine/core/engine.hpp>

// test component class that adds a shared test_int field
class TestComponent : public Component {
    public:
        TestComponent(int test_int)
            , test_int0() { } 

        // note the ref
        int& test_int0;
};

class ExtraComponent : public Component {
    public:
        ExtraComponent(Fields& fields)
            : Component(fields)
            , test_int1(AddField<int>("test_int")) { }

        /* note the template <int> above to indicate
           that we want to share an int "test_int" */
        int& test_int1;
};

/* test entity that adds a TestComponent and ExtraComponent
   that will share the same test_int */
class TestEntity : public Entity { 
    public:
        TestEntity(int test_int = 0)
            : test_component(AddComponent<TestComponent>(test_int)) 
            , extra_component(AddComponent<ExtraComponent>()) { }
    
    TestComponent& test_component;
    ExtraComponent& extra_component;
};

TEST(Component, AddField) {
    Engine engine = Engine();

    // TestComponent and Extracomponent share test_int
    TestEntity& entity = engine.AddEntity<TestEntity>(3);
    ASSERT_EQ(entity.test_component.test_int0, 3);
    ASSERT_EQ(entity.test_component.test_int0, entity.extra_component.test_int1);
}
