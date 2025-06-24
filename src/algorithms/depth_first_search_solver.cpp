#include "depth_first_search_solver.h"
#include <algorithm>
#include <iostream>

void DepthFirstSearchSolver::DFS(int vertex, const Graph &adjacencyList)
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
        parent_[nextVertex] = vertex;
        DFS(nextVertex, adjacencyList);
    }
}

vector<int> DepthFirstSearchSolver::Solve(int vertices,
                                    const Graph &adjacencyList,
                                    int startVertex)
{
    parent_ = vector<int>(vertices, -1);
    parent_[startVertex] = startVertex; // Mark the start vertex as its own parent
    DFS(startVertex, adjacencyList);
    return parent_;
}