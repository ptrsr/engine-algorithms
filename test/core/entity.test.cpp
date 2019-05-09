#include <gtest/gtest.h>

#include <engine/core/engine.hpp>

// test component class that adds a shared test_int field
class TestComponent : public Component {
    public:
        TestComponent(Fields& fields, int test_int)
            : Component(fields)
            , test_int(test_int) { }

        int test_int;
};

// test entity class that adds a TestComponent
class TestEntity : public Entity { 
    public:
        TestEntity(int test_int = 0)
            : test_component(AddComponent<TestComponent>(test_int)) { }
    
    TestComponent& test_component;
};

// test entity to check non existance of component
class NullEntity : public Entity { };

TEST(Entity, AddComponent) {
    Engine engine = Engine();

    // forwarding arguments to component constructor
    TestEntity& test_entity = engine.AddEntity<TestEntity>(1);
    ASSERT_EQ(test_entity.test_component.test_int, 1);
}

TEST(Entity, CheckComponent) {
    Engine engine = Engine();
    
    // NullEntity has no TestComponent
    ASSERT_FALSE(engine.AddEntity<NullEntity>().CheckComponent<TestComponent>());
    // TestEntity has TestComponent
    ASSERT_TRUE(engine.AddEntity<TestEntity>().CheckComponent<TestComponent>());
}

TEST(Entity, GetComponent) {
    Engine engine = Engine();

    TestEntity& test_entity = engine.AddEntity<TestEntity>();

    // GetComponent returns same component that was previously added
    TestComponent& ref0 = test_entity.test_component;
    TestComponent& ref1 = test_entity.GetComponent<TestComponent>();
    ASSERT_EQ(&ref0, &ref1);
}
