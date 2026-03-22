#include "mutex.hpp"

#include <gtest/gtest.h>
#include <thread>
#include <vector>

namespace futex::tests {
TEST(MutexTest, BasicLockUnlock) {
    Mutex m;
    EXPECT_NO_THROW(m.lock());
    EXPECT_NO_THROW(m.unlock());
}

TEST(MutexTest, MutexUsing) {
    Mutex mutex;
    std::size_t
        counter = 0,
        threads_num = 10,
        iterations = 100;
    std::vector<std::thread> threads;
    threads.reserve(threads_num);

    for (std::size_t i = 0; i < threads_num; ++i) {
        threads.emplace_back([&mutex, &counter, iterations]()
        {
            for (std::size_t j = 0; j < iterations; ++j) {
                mutex.lock();
                ++counter;
                mutex.unlock();
            }
        });
    }

    for (auto& t : threads) { t.join(); }

    EXPECT_EQ(counter, threads_num * iterations);
}
}  // namespace futex::tests

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
