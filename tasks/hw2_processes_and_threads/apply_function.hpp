#pragma once

#include <functional>
#include <thread>
#include <vector>

namespace processes_and_threads {
template <typename T>
void ApplyFunction(std::vector<T>& data, const std::function<void(T&)>& transform, const int threadCount = 1) {
    if (data.empty()) return;
    if (threadCount < 1) return;

    const std::size_t threadCountLocal = data.size() < threadCount ? data.size() : threadCount;

    if (threadCountLocal == 1) {
        for (auto& el : data) transform(el);
    } else {
        std::vector<std::thread> threads;
        threads.reserve(threadCountLocal);

        const std::size_t chunkSize = data.size() / threadCountLocal;
        const std::size_t mod = data.size() % threadCountLocal;

        std::size_t startPos = 0;
        std::size_t endPos;
        for (std::size_t i = 0; i < threadCountLocal; ++i) {
            endPos = startPos + chunkSize + (i < mod);
            threads.emplace_back([&data, &transform, startPos, endPos](){
                for (std::size_t j = startPos; j < endPos; ++j) {
                    transform(data[j]);
                }
            });
            startPos = endPos;
        }

        for (auto& thread : threads) thread.join();
    }
}
}  // namespace processes_and_threads