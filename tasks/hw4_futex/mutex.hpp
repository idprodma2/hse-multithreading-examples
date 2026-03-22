#pragma once

#include <atomic>
#include <linux/futex.h>
#include <sys/syscall.h>
#include <unistd.h>

namespace futex {
class Mutex {
public:
    enum State {
        Unlocked,
        Locked,
        LockedWait
    };

    void lock() {
        if (state_.exchange(State::Locked, std::memory_order_acquire) == State::Unlocked) {
            return;
        }

        while (state_.exchange(State::LockedWait, std::memory_order_acquire) != State::Unlocked) {
            syscall(SYS_futex, &state_, FUTEX_WAIT_PRIVATE, State::LockedWait, nullptr, nullptr, 0);
        }
    }

    void unlock() {
        if (state_.exchange(State::Unlocked, std::memory_order_release) == State::LockedWait) {
            syscall(SYS_futex, &state_, FUTEX_WAKE_PRIVATE, State::Locked, nullptr, nullptr, 0);
        }
    }

private:
    std::atomic<State> state_{State::Unlocked};
};
}  // namespace futex