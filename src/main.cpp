#include "random.hpp"
#include "concurrent_random.hpp"
#include "spinlock.hpp"
#include <benchmark/benchmark.h>
#include <random>
#include <mutex>

#define BENCHMARK_PRNG_SEED 0x8bd88b12a5e9edda

template<typename PRNG, typename Lock>
static inline void lock(benchmark::State& state)
{
    PRNG prng{ BENCHMARK_PRNG_SEED };
    benchmark::DoNotOptimize(prng);
    Lock lock;

    for (auto _ : state)
    {
        std::lock_guard guard(lock);

        auto first  = std::uniform_int_distribution{ 0, 100 }(prng);
        auto second = std::uniform_real_distribution{ 0.0, 1.0 }(prng);

        benchmark::DoNotOptimize(first);
        benchmark::DoNotOptimize(second);
    }
}

template<typename PRNG>
static inline void lockfree(benchmark::State& state)
{
    PRNG prng{ BENCHMARK_PRNG_SEED };
    benchmark::DoNotOptimize(prng);

    for (auto _ : state)
    {
        auto first  = std::uniform_int_distribution{ 0, 100 }(prng);
        auto second = std::uniform_real_distribution{ 0.0, 1.0 }(prng);

        benchmark::DoNotOptimize(first);
        benchmark::DoNotOptimize(second);
    }
}

template<typename PRNG>
static inline void threadlocal(benchmark::State& state)
{
    thread_local PRNG prng{ BENCHMARK_PRNG_SEED };
    benchmark::DoNotOptimize(prng);

    for (auto _ : state)
    {
        auto first = std::uniform_int_distribution{ 0, 100 }(prng);
        auto second = std::uniform_real_distribution{ 0.0, 1.0 }(prng);

        benchmark::DoNotOptimize(first);
        benchmark::DoNotOptimize(second);
    }
}


#define NTHREADS 1,8

BENCHMARK_TEMPLATE(lock, dummy_generator, std::mutex)->ThreadRange(NTHREADS);
BENCHMARK_TEMPLATE(lock, splitmix64, std::mutex)->ThreadRange(NTHREADS);
BENCHMARK_TEMPLATE(lock, xoroshiro128p, std::mutex)->ThreadRange(NTHREADS);

BENCHMARK_TEMPLATE(lock, dummy_generator, spinlock)->ThreadRange(NTHREADS);
BENCHMARK_TEMPLATE(lock, splitmix64, spinlock)->ThreadRange(NTHREADS);
BENCHMARK_TEMPLATE(lock, xoroshiro128p, spinlock)->ThreadRange(NTHREADS);

BENCHMARK_TEMPLATE(lockfree, dummy_generator)->ThreadRange(NTHREADS);
BENCHMARK_TEMPLATE(lockfree, splitmix64_atomic)->ThreadRange(NTHREADS);
BENCHMARK_TEMPLATE(lockfree, xorshift64s_atomic)->ThreadRange(NTHREADS);

BENCHMARK_TEMPLATE(threadlocal, dummy_generator)->ThreadRange(NTHREADS);
BENCHMARK_TEMPLATE(threadlocal, splitmix64)->ThreadRange(NTHREADS);
BENCHMARK_TEMPLATE(threadlocal, xoroshiro128p)->ThreadRange(NTHREADS);
