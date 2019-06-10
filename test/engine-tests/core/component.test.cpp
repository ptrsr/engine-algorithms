#include <gtest/gtest.h>

#include <engine/core/scene.hpp>

namespace {
    class MockComponent : public Component {
    private:
        bool& on_removal;

    public:
        bool on_init = false;

        MockComponent(Entity* const entity, bool& on_removal)
            : Component(entity)
            , on_removal(on_removal)
            { }

        void Init(Scene& scene) override {
            on_init = true;
        }

        ~MockComponent() {
            on_removal = true;
        }

        virtual Component_ptr Clone(Entity* const entity) override {
            return Component_ptr(new MockComponent(entity, on_removal));
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

    TEST(ComponentTest, Constructor) {
        // on init is false when instantiating Component directly
        bool tmp = false;
        ASSERT_FALSE(MockComponent(nullptr, tmp).on_init);

        Scene scene = Scene();
        MockEntity& entity = scene.AddEntity<MockEntity>(tmp);

        // reference to entity
        ASSERT_EQ(&entity, entity.mock_component.entity);

        // Init is called through Entity during AddEntity
        ASSERT_TRUE(entity.mock_component.on_init);
    }

    TEST(ComponentTest, Clone) {
        Scene scene;
        bool removed = false;

        MockEntity& original = scene.AddEntity<MockEntity>(removed);
        MockEntity& copy = scene.CloneEntity(original);

        ASSERT_NE(&original.mock_component, &copy.mock_component);
    }

    TEST(ComponentTest, Destructor) {
        Scene scene;
        bool removed = false;

        MockEntity& entity = scene.AddEntity<MockEntity>(removed);
        
        // removed equals true after calling destructor of MockEntity
        scene.DeleteEntity(entity);
        ASSERT_TRUE(removed);
    }
}
