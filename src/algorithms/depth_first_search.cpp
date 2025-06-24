#include "depth_first_search.h"
#include <algorithm>
#include <iostream>

vector<pair<int, int>> DepthFirstSearch::SpanningTree(int vertices,
                                                      const Graph &adjacencyList)
{
    spanningTree_.clear();
    parent_ = vector<int>(vertices, -1);
    DFS(uniform_int_distribution<int>(0, vertices - 1)(generator_), adjacencyList);
    return spanningTree_;
}

void DepthFirstSearch::DFS(int vertex, const Graph &adjacencyList)
{
    vector<int> neighbor_indices(adjacencyList[vertex].size());
    iota(neighbor_indices.begin(), neighbor_indices.end(), 0);
    shuffle(neighbor_indices.begin(), neighbor_indices.end(), generator_);

    for (auto index : neighbor_indices)
    {
        int nextVertex = get<0>(adjacencyList[vertex][index]);
        if (nextVertex < 0 || parent_[nextVertex] != -1)
            continue;
        spanningTree_.emplace_back(vertex, nextVertex);
        parent_[nextVertex] = vertex;
        DFS(nextVertex, adjacencyList);
    }
}