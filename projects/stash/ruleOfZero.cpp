//  <https://cpppatterns.com/patterns/rule-of-zero.html>

#include "gtest/gtest.h"

#include <memory>
#include <vector>

namespace
{
    class foo
    {
    public:
        int x = 10;
        std::vector<int> v = {1, 2, 3, 4, 5};
    };

    class bar
    {
    public:
        std::unique_ptr<int> p = std::make_unique<int>(5);
    };
} // namespace

TEST(RuleOfZeroTest, AssertDefaultCopy)
{
    foo f1;
    foo f2 = f1;

    ASSERT_EQ(f1.x, f2.x);
    ASSERT_EQ(f1.v, f2.v);
}

TEST(RuleOfZeroTest, AssertDefaultMove)
{
    bar b1;
    bar b2 = std::move(b1);
    //bar b3 = b2;  //  Won't compile

    ASSERT_EQ(b1.p, nullptr);
    ASSERT_NE(b2.p, nullptr);
}
