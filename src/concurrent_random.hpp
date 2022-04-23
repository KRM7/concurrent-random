#ifndef CONCURRENT_RANDOM_HPP
#define CONCURRENT_RANDOM_HPP

#include <cstdint>
#include <limits>
#include <array>
#include <bit>
#include <atomic>
#include <cstddef>

class xorshift64s_concurrent final
{
public:
    using result_type = uint64_t;
    using state_type = uint64_t;

    explicit constexpr xorshift64s_concurrent(uint64_t seed) noexcept
        : state(seed)
    {}

    result_type operator()() noexcept
    {
        state_type old_state = state.load(std::memory_order::relaxed);

        for (;;)
        {
            state_type new_state = old_state;
            new_state ^= new_state >> 12;
            new_state ^= new_state << 25;
            new_state ^= new_state >> 27;

            if (state.compare_exchange_weak(old_state, new_state, std::memory_order::release, std::memory_order::relaxed))
            {
                return new_state * 0x2545F4914F6CDD1DULL;
            }
        }
    }

    static constexpr result_type min() noexcept
    {
        return std::numeric_limits<result_type>::min();
    }
    static constexpr result_type max() noexcept
    {
        return std::numeric_limits<result_type>::max();
    }

private:
    std::atomic<state_type> state;
};

class splitmix64_atomic final
{
public:
    using result_type = uint64_t;
    using state_type = uint64_t;

    explicit constexpr splitmix64_atomic(state_type seed) noexcept
        : state(seed)
    {}

    result_type operator()() noexcept
    {
        result_type z = state.fetch_add(0x9e3779b97f4a7c15, std::memory_order::acquire) + 0x9e3779b97f4a7c15;
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
        
        return z ^ (z >> 31);
    }

    static constexpr result_type min() noexcept
    {
        return std::numeric_limits<result_type>::min();
    }
    static constexpr result_type max() noexcept
    {
        return std::numeric_limits<result_type>::max();
    }

private:
    std::atomic<state_type> state;
};

template<typename Lock>
class splitmix64_lock final
{
public:
    using result_type = uint64_t;
    using state_type = uint64_t;

    explicit constexpr splitmix64_lock(uint64_t seed) noexcept
        : state(seed)
    {}

    constexpr result_type operator()() noexcept
    {
        lock.lock();
        state += 0x9e3779b97f4a7c15;
        result_type z = state;
        lock.unlock();

        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
        z = (z ^ (z >> 27)) * 0x94d049bb133111eb;

        return z ^ (z >> 31);
    }

    static constexpr result_type min() noexcept
    {
        return std::numeric_limits<result_type>::min();
    }
    static constexpr result_type max() noexcept
    {
        return std::numeric_limits<result_type>::max();
    }

private:
    state_type state;
    Lock lock;
};

class xoroshiro64ss_concurrent final
{
public:
    using state_type = uint64_t;
    using result_type = uint32_t;

    explicit constexpr xoroshiro64ss_concurrent(result_type seed)
        : state(seed)
    {}

    result_type operator()() noexcept
    {
        state_type old_state = state.load(std::memory_order::relaxed);
        
        for (;;)
        {
            uint32_t s0 = old_state >> 32;
            uint32_t s1 = old_state;

            result_type result = std::rotl(s0 * 0x9E3779BB, 5) * 5;

            s1 ^= s0;
            s0 = std::rotl(s0, 26) ^ s1 ^ (s1 << 9);
            s1 = std::rotl(s1, 13);

            state_type new_state = state_type(s0) << 32 | s1;

            if (state.compare_exchange_weak(old_state, new_state, std::memory_order::release, std::memory_order::relaxed))
            {
                return result;
            }
        }
    }

    static constexpr result_type min() noexcept
    {
        return std::numeric_limits<result_type>::min();
    }
    static constexpr result_type max() noexcept
    {
        return std::numeric_limits<result_type>::max();
    }

private:
    std::atomic<state_type> state;
};

#endif