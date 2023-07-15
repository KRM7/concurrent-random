```shell
clang-cl version 15.0.1 -std:c++20 -O2 -flto -DNDEBUG
```

```shell
random --benchmark_enable_random_interleaving=true --benchmark_repetitions=5
```

```text
---------------------------------------------------------------------------------------------
Benchmark                                                   Time             CPU   Iterations
---------------------------------------------------------------------------------------------
// threads = 1

    // std::mutex
lock<dummy_generator, std::mutex>/threads:1_median       38.7 ns         38.4 ns            5
lock<splitmix64, std::mutex>/threads:1_median            43.5 ns         43.9 ns            5
lock<xoroshiro128p, std::mutex>/threads:1_median         42.5 ns         42.9 ns            5

    // spinlock
lock<dummy_generator, spinlock>/threads:1_median         12.2 ns         12.3 ns            5
lock<splitmix64, spinlock>/threads:1_median              13.5 ns         13.4 ns            5
lock<xoroshiro128p, spinlock>/threads:1_median           13.0 ns         12.9 ns            5

    // lockfree
lockfree<dummy_generator>/threads:1_median              0.894 ns        0.900 ns            5
lockfree<splitmix64_atomic>/threads:1_median             38.0 ns         38.5 ns            5
lockfree<xorshift64s_atomic>/threads:1_median            34.2 ns         33.8 ns            5

    // threadlocal
threadlocal<dummy_generator>/threads:1_median           0.891 ns        0.900 ns            5
threadlocal<splitmix64>/threads:1_median                 7.87 ns         7.95 ns            5
threadlocal<xoroshiro128p>/threads:1_median              7.03 ns         6.98 ns            5


// threads = 4

    // std::mutex
lock<dummy_generator, std::mutex>/threads:4_median       10.8 ns         43.9 ns            5
lock<splitmix64, std::mutex>/threads:4_median            12.7 ns         48.8 ns            5
lock<xoroshiro128p, std::mutex>/threads:4_median         12.2 ns         48.0 ns            5

    // spinlock
lock<dummy_generator, spinlock>/threads:4_median         4.95 ns         19.3 ns            5
lock<splitmix64, spinlock>/threads:4_median              5.32 ns         20.1 ns            5
lock<xoroshiro128p, spinlock>/threads:4_median           5.25 ns         20.2 ns            5

    // lockfree
lockfree<dummy_generator>/threads:4_median              0.445 ns         1.78 ns            5
lockfree<splitmix64_atomic>/threads:4_median             11.9 ns         46.0 ns            5
lockfree<xorshift64s_atomic>/threads:4_median            9.75 ns         38.4 ns            5

    // threadlocal
threadlocal<dummy_generator>/threads:4_median           0.451 ns         1.74 ns            5
threadlocal<splitmix64>/threads:4_median                 3.10 ns         12.6 ns            5
threadlocal<xoroshiro128p>/threads:4_median              2.55 ns         10.0 ns            5


// threads = 8

    // std::mutex
lock<dummy_generator, std::mutex>/threads:8_median       9.56 ns         42.1 ns            5
lock<splitmix64, std::mutex>/threads:8_median            10.3 ns         48.0 ns            5
lock<xoroshiro128p, std::mutex>/threads:8_median         10.6 ns         45.8 ns            5

    // spinlock
lock<dummy_generator, spinlock>/threads:8_median         4.30 ns         18.3 ns            5
lock<splitmix64, spinlock>/threads:8_median              4.74 ns         20.6 ns            5
lock<xoroshiro128p, spinlock>/threads:8_median           4.54 ns         21.0 ns            5

    // lockfree
lockfree<dummy_generator>/threads:8_median              0.378 ns         1.79 ns            5
lockfree<splitmix64_atomic>/threads:8_median             9.41 ns         43.0 ns            5
lockfree<xorshift64s_atomic>/threads:8_median            8.71 ns         35.6 ns            5

    // threadlocal
threadlocal<dummy_generator>/threads:8_median           0.405 ns         1.74 ns            5
threadlocal<splitmix64>/threads:8_median                 2.91 ns         12.0 ns            5
threadlocal<xoroshiro128p>/threads:8_median              2.15 ns         9.88 ns            5

```
