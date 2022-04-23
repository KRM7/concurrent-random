#include "random.hpp"
#include "concurrent_random.hpp"
#include "benchmark/benchmark.h"
#include <random>
#include <mutex>
#include "spinlock.hpp"

thread_local inline splitmix64 prng0{ std::random_device{}() };
thread_local inline xoroshiro128p prng1{ std::random_device{}() };
thread_local inline sfc64 prng2{ std::random_device{}() };

template<typename PRNG, typename Lock>
void lock(benchmark::State& state)
{
    PRNG prng{ std::random_device{}() };
    Lock lock;
    std::uniform_int_distribution int_dist(0, 100);
    std::uniform_real_distribution float_dist(0.0, 1.0);

    for (auto _ : state)
    {
        std::lock_guard guard(lock);
        benchmark::DoNotOptimize(int_dist(prng));
        benchmark::DoNotOptimize(float_dist(prng));
    }
}

template<typename PRNG>
void threadlocal(benchmark::State& state)
{
    thread_local PRNG prng{ std::random_device{}() };
    std::uniform_int_distribution int_dist(0, 100);
    std::uniform_real_distribution float_dist(0.0, 1.0);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(int_dist(prng));
        benchmark::DoNotOptimize(float_dist(prng));
    }
}

template<typename PRNG>
void lockfree(benchmark::State& state)
{
    PRNG prng{ std::random_device{}() };
    std::uniform_int_distribution int_dist(0, 100);
    std::uniform_real_distribution float_dist(0.0, 1.0);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(int_dist(prng));
        benchmark::DoNotOptimize(float_dist(prng));
    }
}

#define NTHREADS 1, 8

BENCHMARK_TEMPLATE(lockfree, splitmix64_lock<std::mutex>)->ThreadRange(NTHREADS);
BENCHMARK_TEMPLATE(lock, xoroshiro128p, std::mutex)->ThreadRange(NTHREADS);
BENCHMARK_TEMPLATE(lock, sfc64, std::mutex)->ThreadRange(NTHREADS);

BENCHMARK_TEMPLATE(threadlocal, splitmix64)->ThreadRange(NTHREADS);
BENCHMARK_TEMPLATE(threadlocal, xoroshiro128p)->ThreadRange(NTHREADS);
BENCHMARK_TEMPLATE(threadlocal, sfc64)->ThreadRange(NTHREADS);

BENCHMARK_TEMPLATE(lockfree, splitmix64_atomic)->ThreadRange(NTHREADS);
BENCHMARK_TEMPLATE(lockfree, xoroshiro64ss_concurrent)->ThreadRange(NTHREADS);
BENCHMARK_TEMPLATE(lockfree, xorshift64s_concurrent)->ThreadRange(NTHREADS);

BENCHMARK_TEMPLATE(lockfree, splitmix64_lock<spinlock>)->ThreadRange(NTHREADS);
BENCHMARK_TEMPLATE(lock, xoroshiro128p, spinlock)->ThreadRange(NTHREADS);
BENCHMARK_TEMPLATE(lock, sfc64, spinlock)->ThreadRange(NTHREADS);

BENCHMARK_MAIN();