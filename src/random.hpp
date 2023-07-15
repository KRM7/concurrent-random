#ifndef BENCHMARK_RANDOM_HPP
#define BENCHMARK_RANDOM_HPP

#include <array>
#include <limits>
#include <bit>
#include <cstddef>
#include <cstdint>

class splitmix64
{
public:
    using result_type = uint64_t;
    using state_type  = uint64_t;

    explicit constexpr splitmix64(uint64_t seed) noexcept :
        state(seed)
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

class xoroshiro128p
{
public:
    using result_type = uint64_t;
    using state_type  = std::array<uint64_t, 2>;

    explicit constexpr xoroshiro128p(uint64_t seed) noexcept
    {
        splitmix64 seed_seq_gen(seed);
        state = { seed_seq_gen(), seed_seq_gen() };
    }

    constexpr result_type operator()() noexcept
    {
        const auto result = state[0] + state[1];
        const auto xstate = state[0] ^ state[1];

        state[0] = std::rotl(state[0], 24) ^ xstate ^ (xstate << 16);
        state[1] = std::rotl(xstate, 37);

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
    state_type state;
};

class dummy_generator
{
public:
    using result_type = uint64_t;

    explicit constexpr dummy_generator(uint64_t) noexcept {}

    constexpr result_type operator()() noexcept
    {
        return 1;
    }

    static constexpr result_type min() noexcept
    {
        return std::numeric_limits<result_type>::min();
    }
    static constexpr result_type max() noexcept
    {
        return std::numeric_limits<result_type>::max();
    }
};

#endif // !BENCHMARK_RANDOM_HPP
