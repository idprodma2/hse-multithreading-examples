#pragma once

#include <coroutine>
#include <optional>

namespace dfs::promise {
template <typename T>
class Async {
public:
    struct promise_type {
        std::optional<T> value_;

        Async get_return_object() {
            return Async{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::suspend_always initial_suspend() {
            return {};
        }

        std::suspend_always final_suspend() noexcept {
            return {};        
        }
    
        std::suspend_always yield_value(T val) {
            value_ = std::move(val);
            return {};
        }

        void return_void() {}

        void unhandled_exception() {
            std::terminate();
        }
    };

    explicit Async(std::coroutine_handle<promise_type> handle) : handle_(handle)
    {}

    ~Async() {
        if (handle_) handle_.destroy();
    }

    bool Next() {
        handle_.resume();
        return !handle_.done();
    }

    T Value() const {
        return *handle_.promise().value_;
    }

private:
    std::coroutine_handle<promise_type> handle_;
};
}  // namespace dfs::promise