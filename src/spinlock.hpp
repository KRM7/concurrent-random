#ifndef BENCHMARK_SPINLOCK_HPP
#define BENCHMARK_SPINLOCK_HPP

#include <atomic>

#if defined(__GNUC__) || defined(__clang__)
    #define SPINLOCK_PAUSE() __builtin_ia32_pause()
#elif defined(_MSC_VER)
    #define SPINLOCK_PAUSE() _mm_pause()
#else
    #define SPINLOCK_PAUSE() (void)0
#endif

class spinlock
{
public:
    void lock() noexcept
    {
        while (true)
        {
            if (!locked_.test_and_set(std::memory_order::acquire))
            {
                break;
            }
            while (locked_.test(std::memory_order::relaxed))
            {
                SPINLOCK_PAUSE();
            }
        }
    }

    bool try_lock() noexcept
    {
        return !locked_.test(std::memory_order::relaxed) && 
               !locked_.test_and_set(std::memory_order::acquire);
    }

    void unlock() noexcept
    {
        locked_.clear(std::memory_order::release);
    }

private:
    std::atomic_flag locked_;
};

#endif // !BENCHMARK_SPINLOCK_HPP
