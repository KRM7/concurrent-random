------------------------------------------------------------------------------------------
Benchmark                                                Time             CPU   Iterations
------------------------------------------------------------------------------------------
splitmix64_lock<std::mutex>/threads:1                  338 ns          280 ns      2563269
splitmix64_lock<std::mutex>/threads:2                  233 ns          359 ns      2000000
splitmix64_lock<std::mutex>/threads:4                  143 ns          458 ns      2560000
splitmix64_lock<std::mutex>/threads:8                  130 ns          432 ns      1991112

lock<xoroshiro128p, std::mutex>/threads:1              171 ns          151 ns      5600000
lock<xoroshiro128p, std::mutex>/threads:2             95.5 ns          177 ns      3446154
lock<xoroshiro128p, std::mutex>/threads:4             99.5 ns          272 ns      2240000
lock<xoroshiro128p, std::mutex>/threads:8             63.6 ns          235 ns      2986664

lock<sfc64, std::mutex>/threads:1                      170 ns          157 ns      4480000
lock<sfc64, std::mutex>/threads:2                      102 ns          166 ns      3584000
lock<sfc64, std::mutex>/threads:4                     69.4 ns          227 ns      3584000
lock<sfc64, std::mutex>/threads:8                     67.7 ns          207 ns      3087752



threadlocal<splitmix64>/threads:1                     17.2 ns         14.8 ns     49777778
threadlocal<splitmix64>/threads:2                     9.67 ns         16.0 ns     38956522
threadlocal<splitmix64>/threads:4                     7.17 ns         20.6 ns     44800000
threadlocal<splitmix64>/threads:8                     9.37 ns         20.4 ns     39822224

threadlocal<xoroshiro128p>/threads:1                  38.1 ns         22.5 ns     26352941
threadlocal<xoroshiro128p>/threads:2                  15.5 ns         24.4 ns     22400000
threadlocal<xoroshiro128p>/threads:4                  10.9 ns         28.3 ns     29866668
threadlocal<xoroshiro128p>/threads:8                  8.92 ns         23.5 ns     29866664

threadlocal<sfc64>/threads:1                          22.9 ns         17.1 ns     44800000
threadlocal<sfc64>/threads:2                          18.9 ns         20.4 ns     34461538
threadlocal<sfc64>/threads:4                          7.47 ns         23.0 ns     22400000
threadlocal<sfc64>/threads:8                          8.61 ns         25.5 ns     25088000



lockfree<splitmix64_atomic>/threads:1                 49.9 ns         43.2 ns     14451613
lockfree<splitmix64_atomic>/threads:2                 68.8 ns         49.7 ns     17920000
lockfree<splitmix64_atomic>/threads:4                 34.8 ns         45.4 ns     16865880
lockfree<splitmix64_atomic>/threads:8                 23.7 ns         57.8 ns     14336000

lockfree<xoroshiro64ss_concurrent>/threads:1          87.2 ns         60.9 ns     10000000
lockfree<xoroshiro64ss_concurrent>/threads:2          32.7 ns         53.0 ns     11200000
lockfree<xoroshiro64ss_concurrent>/threads:4          19.0 ns         61.5 ns     11946668
lockfree<xoroshiro64ss_concurrent>/threads:8          20.2 ns         68.0 ns     13784616

lockfree<xorshift64s_concurrent>/threads:1            41.6 ns         36.8 ns     18666667
lockfree<xorshift64s_concurrent>/threads:2            23.7 ns         39.8 ns     14933334
lockfree<xorshift64s_concurrent>/threads:4            14.7 ns         38.5 ns     13784616
lockfree<xorshift64s_concurrent>/threads:8            10.1 ns         44.1 ns     15582608



splitmix64_lock<spinlock>/threads:1                   32.9 ns         23.7 ns     26352941
splitmix64_lock<spinlock>/threads:2                   21.2 ns         34.9 ns     22400000
splitmix64_lock<spinlock>/threads:4                   15.9 ns         43.2 ns     16290908
splitmix64_lock<spinlock>/threads:8                   11.8 ns         38.4 ns     16290912

lock<xoroshiro128p, spinlock>/threads:1               21.4 ns         19.0 ns     28000000
lock<xoroshiro128p, spinlock>/threads:2               15.5 ns         25.8 ns     22400000
lock<xoroshiro128p, spinlock>/threads:4               10.1 ns         30.5 ns     25600000
lock<xoroshiro128p, spinlock>/threads:8               7.06 ns         27.2 ns     22400000

lock<sfc64, spinlock>/threads:1                       20.8 ns         19.5 ns     34461538
lock<sfc64, spinlock>/threads:2                       12.0 ns         24.4 ns     22400000
lock<sfc64, spinlock>/threads:4                       8.26 ns         31.2 ns     23069424
lock<sfc64, spinlock>/threads:8                       7.85 ns         31.2 ns     32581816