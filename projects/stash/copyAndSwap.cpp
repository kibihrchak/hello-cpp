//  <https://cpppatterns.com/patterns/copy-and-swap.html>

#include "gtest/gtest.h"

#include <utility>

namespace
{
    struct resource
    {
        int x = 0;
    };

    class foo;

    void swap(foo &first, foo &second);

    class foo
    {
    public:
        foo()
            : p{new resource{}}
        {
        }

        foo(const foo &other)
            : p{new resource{*(other.p)}}
        {
        }

        foo(foo &&other)
            : p{other.p}
        {
            other.p = nullptr;
        }

        foo &operator=(foo other)
        {
            swap(*this, other);

            return *this;
        }

        ~foo()
        {
            delete p;
        }

        friend void swap(foo &first, foo &second)
        {
            using std::swap;

            swap(first.p, second.p);
        }

    public:
        resource *p;
    };
} // namespace

TEST(CopyAndSwapTest, AssertCopy)
{
    foo f1, f2;

    ASSERT_NE(f1.p, nullptr);
    ASSERT_NE(f2.p, nullptr);
    ASSERT_NE(f1.p, f2.p);

    f1 = f2;

    ASSERT_NE(f1.p, nullptr);
    ASSERT_NE(f2.p, nullptr);
    ASSERT_EQ(f1.p->x, f2.p->x);
}

TEST(CopyAndSwapTest, AssertMove)
{
    foo f1, f2;

    ASSERT_NE(f1.p, nullptr);
    ASSERT_NE(f2.p, nullptr);
    ASSERT_NE(f1.p, f2.p);

    resource *f2p = f2.p;

    f1 = std::move(f2);

    ASSERT_EQ(f2.p, nullptr);
    ASSERT_EQ(f1.p, f2p);
}
