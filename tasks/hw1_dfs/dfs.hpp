#pragma once

#include <stack>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "promise.hpp"

namespace dfs {
class Graph {
public:
    explicit Graph(const std::size_t size) : matrix_(size)
    {}

    Graph(std::vector<std::vector<std::size_t>>&& matrix) : matrix_(std::move(matrix))
    {}

    void add(std::size_t u, std::size_t v) {
        if (matrix_.size() <= u || matrix_.size() <= v) {
            throw std::invalid_argument("wrong dimensions");
        }
    
        matrix_[u].push_back(v);
        matrix_[v].push_back(u);
    }

    std::size_t size() const {
        return matrix_.size();
    }

    const std::vector<std::size_t>& get_nearest(std::size_t v) const {
        return matrix_[v];
    }

private:
    std::vector<std::vector<std::size_t>> matrix_;
};

promise::Async<std::size_t> dfs(const Graph& graph, std::size_t start_index) {
    std::unordered_set<std::size_t> visited;
    std::stack<std::size_t> st;
    st.push(start_index);

    while (!st.empty()) {
        auto v = st.top();
        st.pop();

        if (visited.contains(v)) {
            continue;
        }

        visited.insert(v);
        co_yield v;

        for (const auto& u : graph.get_nearest(v)) {
            if (!visited.contains(u)) {
                st.push(u);
            }
        }
    }
    
}
}  // namespace dfs