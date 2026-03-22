#include "apply_function.hpp"

#include <benchmark/benchmark.h>
#include <numeric>

namespace processes_and_threads::benchmark {
static void Benchmark_LightFunctionToApply(::benchmark::State& state) {
    const auto size = state.range(0);
    const auto threadsCount = state.range(1);
    std::vector<int> data(size);

    for (const auto& _ : state) {
        state.PauseTiming();
        std::iota(data.begin(), data.end(), 0);
        state.ResumeTiming();

        ApplyFunction<int>(data, [](int& x){x++;}, threadsCount);
    }
}

static void Benchmark_HeavyFunctionToApply(::benchmark::State& state) {
    const auto size = state.range(0);
    const auto threadsCount = state.range(1);
    std::vector<double> data(size);

    for (const auto& _ : state) {
        state.PauseTiming();
        std::iota(data.begin(), data.end(), 0);
        state.ResumeTiming();

        ApplyFunction<double>(data, [](double& x){auto _ = std::to_string(x);}, threadsCount);
    }
}
}  // namespace processes_and_threads::benchmark

BENCHMARK(processes_and_threads::benchmark::Benchmark_LightFunctionToApply)
    ->Args({10, 1})
    ->Args({10, 5})
    ->Args({1000, 1})
    ->Args({1000, 5})
    ->Args({10'000, 1})
    ->Args({10'000, 5})
    ->Unit(benchmark::kMicrosecond)
    ->UseRealTime();

BENCHMARK(processes_and_threads::benchmark::Benchmark_HeavyFunctionToApply)
    ->Args({10, 1})
    ->Args({10, 5})
    ->Args({1000, 1})
    ->Args({1000, 5})
    ->Args({10'000, 1})
    ->Args({10'000, 5})
    ->Args({20'000, 1})
    ->Args({20'000, 5})
    ->Args({20'000, 10})
    ->Unit(benchmark::kMicrosecond)
    ->UseRealTime();

BENCHMARK_MAIN();