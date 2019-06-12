#include <gtest/gtest.h>

#include <engine/core/typemap.hpp>

namespace {
    class MockItem {
    public:
        // virtual copy idiom
        virtual std::shared_ptr<MockItem> Clone(bool cloned) {
            return nullptr;
        }
    };

    class MockMap : public TypeMap<MockItem> { };

    class EmptyItem : public MockItem { };

    class TestItem : public MockItem { 
    public:
        bool test;
        bool cloned = false;

        TestItem(bool test = false)
            : test(test)
            { }

        // copy constructor
        TestItem(const TestItem& original)
            : test(original.test)
            { }

        std::shared_ptr<MockItem> Clone(bool cloned = false) override {
            auto* derived = new TestItem(*this);
            derived->cloned = cloned;
            return std::shared_ptr<MockItem>(derived);
        }
    };

    // typemap test setup
    class TypeMapTest : public ::testing::Test {
    protected:
        MockMap map;
    };

    TEST_F(TypeMapTest, AddBase) {
        {
            // add empty EmptyItem
            auto& item = map.AddBase<EmptyItem>();
            ASSERT_EQ(typeid(EmptyItem), typeid(item));

            // re-adding same type results in returning reference to original object 
            ASSERT_EQ(&item, &map.AddBase<EmptyItem>());
        }
        {
            // add TestItem with constructor parameter forwarding
            TestItem& test_item = map.AddBase<TestItem>(true);
            ASSERT_EQ(typeid(TestItem), typeid(test_item));

            // assert if forwarding worked
            ASSERT_TRUE(test_item.test);
        }
    }

    TEST_F(TypeMapTest, GetBase) {
        // GetBase returns nullptr when no base has been added before
        ASSERT_FALSE(map.GetBase<EmptyItem>());

        map.AddBase<EmptyItem>();

        // GetBase returns a valid pointer to EmptyItem
        auto* item = map.GetBase<EmptyItem>();
        ASSERT_TRUE(item);
        ASSERT_EQ(typeid(EmptyItem), typeid(*item));

        // GetBase still returns nullptr when derived base does not exist
        ASSERT_FALSE(map.GetBase<TestItem>());
    }

    TEST_F(TypeMapTest, Clone) {
        TestItem& item_original = map.AddBase<TestItem>(true);

        /* copy TypeMap with all it's contents and
           forward parameters to Item Clone function */
        auto* copied_map = map.Clone(true);

        // get pointer to copy of item_original
        TestItem* const item = copied_map->GetBase<TestItem>();

        // item pointer is not a nullptr
        ASSERT_TRUE(item);

        // copy does not point to original
        ASSERT_NE(&item_original, item);

        // copied contents have same member values
        ASSERT_TRUE(item->test);

        ASSERT_TRUE(item->cloned);
    }
}
