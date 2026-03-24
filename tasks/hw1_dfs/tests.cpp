#include <gtest/gtest.h>

#include "dfs.hpp"

namespace dfs::tests {
//          0
//         / \
//        1   2
//       /   / \
//      3   4   5
// expected output: 0 1 3 2 4 5 or 0 1 3 2 5 4 or 0 2 4 5 1 3 or 0 2 5 4 1 3

TEST(DfsCoroutineTest, ConstructorWithSize) {
    dfs::Graph graph(6);
    graph.add(0, 2);
    graph.add(0, 1);
    graph.add(2, 5);
    graph.add(2, 4);
    graph.add(1, 3);

    auto async = dfs::dfs(graph, 0);
    std::vector<std::size_t> visited;
    std::vector<std::size_t> expected = {0, 1, 3, 2, 4, 5};
    visited.reserve(6);
    while (async.Next()) {
        visited.push_back(async.Value());
    }

    EXPECT_EQ(visited, expected);
}

TEST(DfsCoroutineTest, ConstructorWithMatrix) {
    dfs::Graph graph{
        {
            {1, 2}, // 0
            {3}, // 1
            {4, 5}, // 2
            {1}, // 3
            {2}, // 4
            {2}, // 5
        }
    };
    auto async = dfs::dfs(graph, 0);
    std::vector<std::size_t> visited;
    std::vector<std::size_t> expected = {0, 2, 5, 4, 1, 3};
    visited.reserve(6);
    while (async.Next()) {
        visited.push_back(async.Value());
    }

    EXPECT_EQ(visited, expected);
}
}  // namespace dfs::tests