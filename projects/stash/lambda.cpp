//  <https://www.youtube.com/watch?v=3jCOwajNch0>
//  <https://github.com/CppCon/CppCon2019/blob/master/Presentations/back_to_basics_lambdas_from_scratch/back_to_basics_lambdas_from_scratch__arthur_odwyer__cppcon_2019.pdf>

#include "gtest/gtest.h"

#include <utility>

namespace
{
    class LambdaClass
    {
        int value;

    public:
        LambdaClass(int v) : value(v) {}

        int operator()(int x) const
        {
            return x + value;
        }
    };

    int g = 10;
} // namespace

TEST(LambdaTest, LambdaClassReplacement)
{
    auto lambdaClass = LambdaClass(1);
    auto lambda = [value = 1](int x) { return x + value; };

    ASSERT_EQ(lambdaClass(42), 43);
    ASSERT_EQ(lambda(42), 43);
}

TEST(LambdaTest, LambdaReference)
{
    int i = 42;
    auto lambda = [&value = i]() { return value + 1; };

    ASSERT_EQ(lambda(), 43);

    i = 12;

    ASSERT_EQ(lambda(), 13);
}

TEST(LambdaTest, MoveConstructor)
{
    std::string foo = "Foo";

    auto lambda = [value = std::move(foo)]() { return value.length(); };

    ASSERT_EQ(foo.length(), 0);
    ASSERT_EQ(lambda(), 3);
}

TEST(LambdaTest, ImplicitCaptureAtInvocation)
{
    auto lambdaFoo = [=]() { return g + 1; };
    auto lambdaBar = [g = g]() { return g + 1; };

    g = 20;

    ASSERT_EQ(lambdaFoo(), 21);
    ASSERT_EQ(lambdaBar(), 11);

    g = 30;

    ASSERT_EQ(lambdaFoo(), 31);
    ASSERT_EQ(lambdaBar(), 11);
}

TEST(LambdaTest, StaticVariable)
{
    auto lambda = []() { static int i; return ++i; };

    auto lambdaCopy = lambda;

    ASSERT_EQ(lambda(), 1);
    ASSERT_EQ(lambdaCopy(), 2);
    ASSERT_EQ(lambda(), 3);
}

TEST(LambdaTest, MutableLambda)
{
    auto lambda = [i = 0]() mutable { return ++i; };

    auto lambdaCopy = lambda;

    ASSERT_EQ(lambda(), 1);
    ASSERT_EQ(lambdaCopy(), 1);
    ASSERT_EQ(lambda(), 2);
}
