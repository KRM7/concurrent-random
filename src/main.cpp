#include "random.hpp"
#include "concurrent_random.hpp"
#include "benchmark/benchmark.h"
#include <random>
#include <mutex>

thread_local splitmix64 prng0{ std::random_device{}() };
thread_local xoroshiro128p prng1{ std::random_device{}() };
thread_local sfc64 prng2{ std::random_device{}() };

std::mutex lock0;
std::mutex lock1;
std::mutex lock2;
splitmix64 prng3{ std::random_device{}() };
xoroshiro128p prng4{ std::random_device{}() };
sfc64 prng5{ std::random_device{}() };

void lockSplitmix64(benchmark::State& state)
{
    std::uniform_int_distribution int_dist(0, 100);
    std::uniform_real_distribution float_dist(0.0, 1.0);

    for (auto _ : state)
    {
        std::lock_guard guard(lock0);
        benchmark::DoNotOptimize(int_dist(prng3));
        benchmark::DoNotOptimize(float_dist(prng3));
    }
}

void lockXoroshiro128p(benchmark::State& state)
{
    std::uniform_int_distribution int_dist(0, 100);
    std::uniform_real_distribution float_dist(0.0, 1.0);

    for (auto _ : state)
    {
        std::lock_guard guard(lock1);
        benchmark::DoNotOptimize(int_dist(prng4));
        benchmark::DoNotOptimize(float_dist(prng4));
    }
}

void lockSfc64(benchmark::State& state)
{
    std::uniform_int_distribution int_dist(0, 100);
    std::uniform_real_distribution float_dist(0.0, 1.0);

    for (auto _ : state)
    {
        std::lock_guard guard(lock2);
        benchmark::DoNotOptimize(int_dist(prng5));
        benchmark::DoNotOptimize(float_dist(prng5));
    }
}

void threadlocalSplitmix64(benchmark::State& state)
{
    std::uniform_int_distribution int_dist(0, 100);
    std::uniform_real_distribution float_dist(0.0, 1.0);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(int_dist(prng0));
        benchmark::DoNotOptimize(float_dist(prng0));
    }
}

void threadlocalXoroshiro128p(benchmark::State& state)
{
    std::uniform_int_distribution int_dist(0, 100);
    std::uniform_real_distribution float_dist(0.0, 1.0);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(int_dist(prng1));
        benchmark::DoNotOptimize(float_dist(prng1));
    }
}

void threadlocalSfc64(benchmark::State& state)
{
    std::uniform_int_distribution int_dist(0, 100);
    std::uniform_real_distribution float_dist(0.0, 1.0);

    for (auto _ : state)
    {
        benchmark::DoNotOptimize(int_dist(prng2));
        benchmark::DoNotOptimize(float_dist(prng2));
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

#define NTHREADS 1, 16

BENCHMARK(lockSplitmix64)->ThreadRange(NTHREADS);
BENCHMARK(lockXoroshiro128p)->ThreadRange(NTHREADS);
BENCHMARK(lockSfc64)->ThreadRange(NTHREADS);
BENCHMARK(threadlocalSplitmix64)->ThreadRange(NTHREADS);
BENCHMARK(threadlocalXoroshiro128p)->ThreadRange(NTHREADS);
BENCHMARK(threadlocalSfc64)->ThreadRange(NTHREADS);
BENCHMARK_TEMPLATE(lockfree, splitmix64_concurrent)->ThreadRange(NTHREADS);
BENCHMARK_TEMPLATE(lockfree, xoroshiro64ss_concurrent)->ThreadRange(NTHREADS);
BENCHMARK_TEMPLATE(lockfree, xorshift64s_concurrent)->ThreadRange(NTHREADS);

BENCHMARK_MAIN();