#ifndef BENCHMARK_SHARED_SPINLOCK_HPP
#define BENCHMARK_SHARED_SPINLOCK_HPP

#include "spinlock.hpp"
#include <atomic>
#include <tuple>

class shared_spinlock
{
public:
    void lock() noexcept
    {
        lock_.lock();
        while (read_cnt_.load(std::memory_order_relaxed));
        std::ignore = read_cnt_.load(std::memory_order_acquire);
    }

    bool try_lock() noexcept
    {
        return lock_.try_lock() && !read_cnt_.load(std::memory_order_acquire);
    }

    void unlock() noexcept
    {
        lock_.unlock();
    }

    void lock_shared() noexcept
    {
        lock_.lock();
        read_cnt_.fetch_add(1, std::memory_order_relaxed);
        lock_.unlock();
    }

    bool try_lock_shared() noexcept
    {
        if (lock_.try_lock())
        {
            read_cnt_.fetch_add(1, std::memory_order_relaxed);
            lock_.unlock();
            return true;
        }
        return false;
    }

    void unlock_shared() noexcept
    {
        read_cnt_.fetch_sub(1, std::memory_order_release);
    }

private:
    std::atomic<uint32_t> read_cnt_;
    spinlock lock_;
};

#endif // !BENCHMARK_SHARED_SPINLOCK_HPP
