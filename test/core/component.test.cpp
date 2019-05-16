#include <gtest/gtest.h>

#include <engine/core/engine.hpp>

namespace {
    class MockComponent : public Component {
    public:
        MockComponent(bool& on_removal)
            : on_removal(on_removal)
            { }

    private:
        ~MockComponent() {
            on_removal = true;
        }
        
        bool& on_removal;
    };

    class MockEntity : public Entity {
    public:
        MockEntity(bool& on_removal) { 
            AddComponent<MockComponent>(on_removal);
        }
    };

    TEST(Component, Destructor) {
        Engine engine = Engine();

        // removed equals true after calling deconstructor of MockEntity
        bool removed = false;
        MockEntity& entity = engine.AddEntity<MockEntity>(removed);
        engine.DeleteEntity(entity);
        ASSERT_TRUE(removed);
    }
}
