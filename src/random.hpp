#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cstdint>
#include <array>
#include <limits>
#include <bit>
#include <cstddef>

class splitmix64 final
{
public:
    using result_type = uint64_t;
    using state_type = uint64_t;

    explicit constexpr splitmix64(uint64_t seed) noexcept
        : state(seed)
    {}

    constexpr result_type operator()() noexcept
    {
        state += 0x9e3779b97f4a7c15;
        result_type z = state;
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
};

class xoroshiro128p final
{
public:
    using result_type = uint64_t;
    using state_type = uint64_t;

    explicit constexpr xoroshiro128p(uint64_t seed) noexcept
    {
        splitmix64 seed_seq_gen(seed);
        state = { seed_seq_gen(), seed_seq_gen() };
    }

    explicit constexpr xoroshiro128p(const std::array<state_type, 2>& state) noexcept
        : state(state)
    {}

    constexpr result_type operator()() noexcept
    {
        const state_type s0 = state[0];
        state_type s1 = state[1];
        const result_type result = s0 + s1;

        s1 ^= s0;
        state[0] = std::rotl<state_type>(s0, 24U) ^ s1 ^ (s1 << 16);
        state[1] = std::rotl<state_type>(s1, 37U);

        return result;
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
    std::array<state_type, 2> state;
};

class sfc64 final
{
public:
    using result_type = uint64_t;
    using state_type = uint64_t;

    explicit constexpr sfc64(uint64_t seed) noexcept
        : state({ seed, seed, seed, 1 })
    {
        warmup();
    }

    explicit constexpr sfc64(std::array<state_type, 4>& state) noexcept
        : state(state)
    {}

    constexpr result_type operator()() noexcept
    {
        result_type ret = state[0] + state[1] + state[3];
        state[3]++;

        state[0] = state[1] ^ (state[1] >> 11);
        state[1] = state[2] + (state[2] << 3);
        state[2] = std::rotl<state_type>(state[2], 24) + ret;

        return ret;
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
    std::array<state_type, 4> state;

    constexpr void warmup() noexcept
    {
        for (size_t i = 0; i < 12; i++) 
        {
            operator()();
        }
    }
};

#endif