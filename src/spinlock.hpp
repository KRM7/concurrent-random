#ifndef BENCHMARK_SPINLOCK_HPP
#define BENCHMARK_SPINLOCK_HPP

#include <atomic>

class spinlock
{
public:
    void lock() noexcept
    {
        while (true)
        {
            if (!locked_.test_and_set(std::memory_order_acquire)) break;
            while (locked_.test(std::memory_order_relaxed));
        }
    }

    bool try_lock() noexcept
    {
        return !locked_.test(std::memory_order_relaxed) && 
               !locked_.test_and_set(std::memory_order_acquire);
    }

    void unlock() noexcept
    {
        locked_.clear(std::memory_order_release);
    }

private:
    std::atomic_flag locked_;
};

#endif // !BENCHMARK_SPINLOCK_HPP
