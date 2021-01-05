//  <https://cpppatterns.com/patterns/rule-of-zero.html>

#include "gtest/gtest.h"

namespace
{
} // namespace

TEST(StaticAssertTest, AssertFalse)
{
    static_assert(false, "Static assert failed");

    ASSERT_TRUE(false);
}
