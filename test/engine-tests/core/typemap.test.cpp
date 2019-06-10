#include <gtest/gtest.h>

#include <engine/core/typemap.hpp>

namespace {
    class MockBase {
    public:
        // virtual copy idiom
        virtual std::shared_ptr<MockBase> Clone() {
            return nullptr;
        }
    };

    class MockMap : public TypeMap<MockBase> { };

    class MockDerived : public MockBase { };

    class TestDerived : public MockBase { 
    public:
        TestDerived(bool test = false)
            : test(test)
            { }

        // copy constructor
        TestDerived(const TestDerived& original)
            : test(original.test)
            { }

        std::shared_ptr<MockBase> Clone() override {
            return std::shared_ptr<MockBase>(new TestDerived(*this));
        }

        bool test;
    };

    // typemap test setup
    class TypeMapTest : public ::testing::Test {
    protected:
        MockMap map;
    };

    TEST_F(TypeMapTest, AddBase) {
        // add empty MockDerived
        MockDerived& derived_base = map.AddBase<MockDerived>();
        ASSERT_EQ(typeid(MockDerived), typeid(derived_base));

        // re-adding same type results in returning reference to original object 
        ASSERT_EQ(&derived_base, &map.AddBase<MockDerived>());

        // add TestDerived with constructor parameter forwarding
        TestDerived& test_base = map.AddBase<TestDerived>(true);
        ASSERT_EQ(typeid(TestDerived), typeid(test_base));

        // assert if forwarding worked
        ASSERT_TRUE(test_base.test);
    }

    TEST_F(TypeMapTest, GetBase) {
        // GetBase returns nullptr when no base has been added before
        ASSERT_FALSE(map.GetBase<MockDerived>());

        map.AddBase<MockDerived>();
        // GetBase returns a valid pointer to MockDerived
        MockDerived* const mock_derived = map.GetBase<MockDerived>();
        ASSERT_TRUE(mock_derived);
        ASSERT_EQ(typeid(MockDerived), typeid(*mock_derived));

        // GetBase does returns nullptr when getting other derived class
        ASSERT_FALSE(map.GetBase<TestDerived>());
    }

    TEST_F(TypeMapTest, Copy) {
        TestDerived& test_base_original = map.AddBase<TestDerived>(true);

        // copy TypeMap with all it's contents
        auto* copied_map = map.Clone();

        // get pointer to copy of test_base_original
        TestDerived* const test_base = copied_map->GetBase<TestDerived>();

        // test_base pointer is not a nullptr
        ASSERT_TRUE(test_base);

        // copy does not point to original
        ASSERT_NE(&test_base_original, test_base);

        // copied contents have same member values
        ASSERT_TRUE(test_base->test);
    }
}
