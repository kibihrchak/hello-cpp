//  <https://cpppatterns.com/patterns/copy-and-swap.html>

#include "gtest/gtest.h"

#include <type_traits>

namespace
{
    template <typename T, typename Enable = void>
    class foo
    {
    public:
        char x{'c'};
    };

    template <typename T>
    class foo<T, typename std::enable_if<std::is_integral<T>::value>::type>
    {
    public:
        int x{2};
    };

    template <>
    class foo<long>
    {
    public:
        int x{20};
    };

    template <typename T>
    class foo<T, typename std::enable_if<std::is_floating_point<T>::value>::type>
    {
    public:
        float x{3.00};
    };
} // namespace

TEST(SfinaeTest, AssertIntegralDeduction)
{
    foo<int> f;

    ASSERT_EQ(f.x, 2);
}

TEST(SfinaeTest, AssertFloatingPointDeduction)
{
    foo<float> f;

    ASSERT_FLOAT_EQ(f.x, 3.00);
}

TEST(SfinaeTest, AssertLongDeduction)
{
    foo<long> f;

    ASSERT_FLOAT_EQ(f.x, 20);
}

TEST(SfinaeTest, AssertDefaultDeduction)
{
    foo<void> f;

    ASSERT_EQ(f.x, 'c');
}
