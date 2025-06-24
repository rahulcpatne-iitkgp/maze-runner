#include "loop_erased_random_walk.h"
#include <algorithm>

vector<pair<int, int>> LoopErasedRandomWalk::SpanningTree(int vertices,
                                                          const Graph &adjacencyList)
{
    spanningTree_.clear();
    visited_ = vector<int>(vertices, 0);

    vector<int> node_order(vertices);
    iota(node_order.begin(), node_order.end(), 0);
    shuffle(node_order.begin(), node_order.end(), generator_);

    visited_[node_order[0]] = 1;
    for (int round = 1, i = 1; i < vertices; ++i)
    {
        if (visited_[node_order[i]])
            continue;
        ++round;
        LERW(node_order[i], round, adjacencyList);
    }

    return spanningTree_;
}

void LoopErasedRandomWalk::LERW(int vertex, int round,
                                const Graph &adjacencyList)
{
    vector<int> current_path;
    while (!visited_[vertex])
    {
        visited_[vertex] = round;
        current_path.push_back(vertex);
        int next_vertex = -1;
        do
        {
            next_vertex = get<0>(adjacencyList[vertex][uniform_int_distribution<int>(
                0, adjacencyList[vertex].size() - 1)(generator_)]);
        } while (next_vertex < 0);

        if (visited_[next_vertex] == round)
        {
            do
            {
                vertex = current_path.back();
                visited_[vertex] = 0;
                current_path.pop_back();
            } while (vertex != next_vertex);
        }

        vertex = next_vertex;
    }

    current_path.push_back(vertex);
    for (size_t i = 0; i < current_path.size() - 1; ++i)
    {
        int u = current_path[i];
        int v = current_path[i + 1];
        spanningTree_.emplace_back(u, v);
    }
}