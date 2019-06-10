#include <gtest/gtest.h>

#include <engine/core/scene.hpp>
#include <engine/core/entity.hpp>

/* NOTE: since Entity is based on TypeMap, most functionality will be tested
   in typemap.test.cpp . here we will test the possiblities of multi inheritance
   for entities. */
namespace {
    class MockComponent : public Component {
    public:
        unsigned test = 0;

        MockComponent(Entity* const entity)
            : Component(entity)
            { }
    };

    typedef std::shared_ptr<MockComponent> MockComponent_ptr;

    class MockEntity : public Entity {
    public:
        MockComponent& mock_component;

        /* constructor that instantiates a new component */
        MockEntity(const unsigned int id = 0)
            : Entity(id)
            , mock_component(AddComponent<MockComponent>())
            { }

        /* constructor that takes a smart pointer to a component.
           this is for shared components */
        MockEntity(const unsigned int id, MockComponent_ptr mock_component)
            : Entity(id)
            , mock_component(AddComponent(mock_component))
            { }
    };

    class InitEntity : public Entity {
    private:
        bool& init;

    public: 
        InitEntity(const unsigned id, bool& init)
            : Entity(id)
            , init(init)
            { }

        void Init(Scene& scene) override {
            init = true;
        }
    };

    TEST(EntityTest, Constructor) {
        {
            MockEntity entity;
            ASSERT_EQ(0, entity.mock_component.test);
        }
        {
            MockComponent_ptr mock_component();
        }
    }

    TEST(EntityTest, Init) {
        Scene scene;
        
        bool init = false;
        scene.AddEntity<InitEntity>(init);
        
        // Component.Init is called on Scene.AddEntity
        ASSERT_TRUE(init);
    }

    // TEST(EntityTest, AddComponent) {
    //     MockEntityC test_entity;

    //     // MockEntityC's MockComponents point to the same MockComponent
    //     ASSERT_EQ(&test_entity.mock_component_a, &test_entity.mock_component_b);
    // }
}
