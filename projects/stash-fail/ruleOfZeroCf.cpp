//  <https://cpppatterns.com/patterns/rule-of-zero.html>

#include "gtest/gtest.h"

#include <memory>

namespace
{
    class bar
    {
    public:
        std::unique_ptr<int> p = std::make_unique<int>(5);
    };
} // namespace

TEST(RuleOfZeroTest, AssertDefaultAssignment)
{
    bar b1;
    bar b2 = b1;

    ASSERT_TRUE(false);
}
