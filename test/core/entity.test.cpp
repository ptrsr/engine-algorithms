#include <gtest/gtest.h>

#include <engine/core/engine.hpp>

// test component class that adds a shared test_int field
class TestComponent : public Component {
    public:
        TestComponent(Fields& fields, int test_int)
            : test_int(fields.AddField("test_int", test_int)) { }

        int& test_int;
};

// test entity class that adds a TestComponent
class TestEntity : public Entity { 
    public:
        TestEntity(int test_int)
            : test_component(AddComponent<TestComponent>(test_int)) { }
    
    TestComponent& test_component;
};

TEST(Component, AddComponent) {
    Engine engine = Engine();
    TestEntity& test_entity = engine.AddEntity<TestEntity>(1);

    ASSERT_EQ(test_entity.test_component.test_int, 1);
}
