//  <https://cpppatterns.com/patterns/pass-values-between-threads.html>
//  <https://www.modernescpp.com/index.php/promise-and-future>
//  <https://www.modernescpp.com/index.php/condition-variables>

#include "gtest/gtest.h"

#include <future>
#include <thread>
#include <mutex>
#include <chrono>

namespace
{
    void set_promise(
        std::promise<int> promise,
        int value,
        std::chrono::duration<int, std::milli> delay)
    {
        std::this_thread::sleep_for(delay);
        promise.set_value(value);
    }

    int wait_future(std::future<int> future)
    {
        return future.get();
    }

    void cv_notify_one(
        std::condition_variable &cv,
        bool &flag,
        std::mutex &mutex,
        std::chrono::duration<int, std::milli> delay)
    {
        std::this_thread::sleep_for(delay);

        std::unique_lock<std::mutex> lock(mutex);
        flag = true;
        cv.notify_one();
    }

    void cv_wait(
        std::condition_variable &cv,
        bool &flag,
        std::mutex &mutex)
    {
        std::unique_lock<std::mutex> lock(mutex);

        while (!flag)
        {
            cv.wait(lock);
        }
    }
} // namespace

TEST(SynchronizationTest, PromiseFuture)
{
    std::promise<int> promise;
    std::future<int> future = promise.get_future();

    using namespace std::chrono_literals;

    std::thread prodThread(set_promise, std::move(promise), 12, 1000ms);
    auto start = std::chrono::high_resolution_clock::now();

    auto result = wait_future(std::move(future));

    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start);

    prodThread.join();

    ASSERT_EQ(result, 12);
    ASSERT_GE(diff.count(), 1000);
}

TEST(SynchronizationTest, ConditionVariable)
{
    std::mutex mutex;
    bool conditionSatisfied{false};
    std::condition_variable cv;

    using namespace std::chrono_literals;

    std::thread cvNotifyThread(
        cv_notify_one,
        std::ref(cv),
        std::ref(conditionSatisfied),
        std::ref(mutex),
        1000ms);
    auto start = std::chrono::high_resolution_clock::now();

    cv_wait(cv, conditionSatisfied, mutex);

    auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start);

    cvNotifyThread.join();

    ASSERT_TRUE(conditionSatisfied);
    ASSERT_GE(diff.count(), 1000);
}
