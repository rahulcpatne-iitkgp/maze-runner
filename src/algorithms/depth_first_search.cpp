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
    // Generate random order of neighbors
    vector<int> neighbor_indices(adjacencyList[vertex].size());
    iota(neighbor_indices.begin(), neighbor_indices.end(), 0);
    shuffle(neighbor_indices.begin(), neighbor_indices.end(), generator_);

    // Visit each neighbor
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

vector<int> DepthFirstSearch::Solve(int vertices,
                                    const Graph &adjacencyList,
                                    int startVertex)
{
    spanningTree_.clear();
    parent_ = vector<int>(vertices, -1);
    parent_[startVertex] = startVertex; // Mark the start vertex as its own parent
    DFS(startVertex, adjacencyList);
    return parent_;
}