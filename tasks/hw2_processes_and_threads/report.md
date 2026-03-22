## Домашнее задание
Реализуйте следующий метод:

template <typename T>
void ApplyFunction(std::vector<T>& data, const std::function<void(T&)>& transform, const int threadCount = 1);
Данный метод должен применить переданную функцию transform к каждому элементу вектора data. threadCount задает количество потоков, которое нужно использовать для применения функции. Если число потоков превышает число элементов, то число потоков следует взять равным числу элементов.

Напишите тесты для вашей реализации с использованием gtest.

Напишите бенчмарк для вашей реализации с использованием benchmark.

В бенчмарке отразите две ситуации -- когда однопоточная версия стабильно быстрее многопоточной и обратную ситуацию. Достигните этого как с помощью подбора размера вектора data, так и с помощью подбора функции transform.

## Результаты
### Автотесты
./apply_function_test
[==========] Running 7 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 1 test from ApplyFunction
[ RUN      ] ApplyFunction.DoNothing
[       OK ] ApplyFunction.DoNothing (0 ms)
[----------] 1 test from ApplyFunction (1 ms total)

[----------] 6 tests from ApplyFunctionTest
[ RUN      ] ApplyFunctionTest.EmptyData
[       OK ] ApplyFunctionTest.EmptyData (0 ms)
[ RUN      ] ApplyFunctionTest.IntegerType
[       OK ] ApplyFunctionTest.IntegerType (0 ms)
[ RUN      ] ApplyFunctionTest.StringType
[       OK ] ApplyFunctionTest.StringType (0 ms)
[ RUN      ] ApplyFunctionTest.DoubleType
[       OK ] ApplyFunctionTest.DoubleType (0 ms)
[ RUN      ] ApplyFunctionTest.CustomType
[       OK ] ApplyFunctionTest.CustomType (0 ms)
[ RUN      ] ApplyFunctionTest.LargeData
[       OK ] ApplyFunctionTest.LargeData (1 ms)
[----------] 6 tests from ApplyFunctionTest (2 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 2 test suites ran. (3 ms total)
[  PASSED  ] 7 tests.

### Бенчмаркинг
Как видно из отчета ниже - для легкой функции быстрее выполняется решение на одном потоке, даже при пачке входных данных побольше.
При этом для тяжелой функции (в данном случае трансформация в строку) с увеличением размера данных для обработки больше проявляется эффективность многопоточного решения.

2026-03-22T15:18:47+03:00
Running ./apply_function_benchmark
Run on (8 X 1190 MHz CPU s)
Load Average: 0.52, 0.58, 0.59
Benchmark                                                                                    Time             CPU   Iterations
------------------------------------------------------------------------------------------------------------------------------
processes_and_threads::benchmark::Benchmark_LightFunctionToApply/10/1/real_time           1.09 us         1.00 us       640345
processes_and_threads::benchmark::Benchmark_LightFunctionToApply/10/5/real_time            177 us          150 us         3747
processes_and_threads::benchmark::Benchmark_LightFunctionToApply/1000/1/real_time         17.4 us         18.9 us        42067
processes_and_threads::benchmark::Benchmark_LightFunctionToApply/1000/5/real_time          178 us          138 us         3975
processes_and_threads::benchmark::Benchmark_LightFunctionToApply/10000/1/real_time         148 us          166 us         3946
processes_and_threads::benchmark::Benchmark_LightFunctionToApply/10000/5/real_time         206 us          166 us         3290
processes_and_threads::benchmark::Benchmark_HeavyFunctionToApply/10/1/real_time           3.51 us         3.53 us       203744
processes_and_threads::benchmark::Benchmark_HeavyFunctionToApply/10/5/real_time            178 us          163 us         4029
processes_and_threads::benchmark::Benchmark_HeavyFunctionToApply/1000/1/real_time          329 us          324 us         2172
processes_and_threads::benchmark::Benchmark_HeavyFunctionToApply/1000/5/real_time          273 us          191 us         2612
processes_and_threads::benchmark::Benchmark_HeavyFunctionToApply/10000/1/real_time        3322 us         3423 us          210
processes_and_threads::benchmark::Benchmark_HeavyFunctionToApply/10000/5/real_time        1670 us          379 us          371
processes_and_threads::benchmark::Benchmark_HeavyFunctionToApply/20000/1/real_time        6869 us         6765 us           97
processes_and_threads::benchmark::Benchmark_HeavyFunctionToApply/20000/5/real_time        3218 us          150 us          209
processes_and_threads::benchmark::Benchmark_HeavyFunctionToApply/20000/10/real_time       2656 us          661 us          260