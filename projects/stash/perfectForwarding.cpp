//  <https://cpppatterns.com/patterns/perfect-forwarding.html>

#include "gtest/gtest.h"

#include <memory>

namespace
{
    struct A
    {
        A(int &&nSrc) : ot(OverloadType::Rvalue), n(nSrc) {}
        A(int &nSrc) : ot(OverloadType::Lvalue), n(nSrc) {}
        A(const int &nSrc) : ot(OverloadType::ConstLvalue), n(nSrc) {}

        enum class OverloadType
        {
            Rvalue,
            Lvalue,
            ConstLvalue,
            Invalid
        };

        OverloadType ot{OverloadType::Invalid};
        int n;
    };

    template <class T, class U>
    std::unique_ptr<T> make_unique(U &&u)
    {
        return std::unique_ptr<T>(new T(std::forward<U>(u)));
    }
} // namespace

TEST(PerfectForwardingTest, Rvalue)
{
    auto a = make_unique<A>(2);

    ASSERT_EQ(a->ot, A::OverloadType::Rvalue);
    ASSERT_EQ(a->n, 2);
}

TEST(PerfectForwardingTest, Lvalue)
{
    int i{20};
    auto a = make_unique<A>(i);

    ASSERT_EQ(a->ot, A::OverloadType::Lvalue);
    ASSERT_EQ(a->n, 20);
}

TEST(PerfectForwardingTest, ConstLvalue)
{
    const int i{200};
    auto a = make_unique<A>(i);

    ASSERT_EQ(a->ot, A::OverloadType::ConstLvalue);
    ASSERT_EQ(a->n, 200);
}
