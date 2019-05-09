#include <gtest/gtest.h>

#include <engine/core/fields.hpp>

TEST(Fields, AddField) {
    Fields fields = Fields();

    // adding field with same name twice results in same references
    float& ref0 = fields.AddField("test_float", 1.0f);
    float& ref1 = fields.AddField<float>("test_float");
    ASSERT_EQ(&ref0, &ref1);

    // check if default init works
    int& ref3 = fields.AddField<int>("test_int");
    ASSERT_EQ(ref3, 0);
}
