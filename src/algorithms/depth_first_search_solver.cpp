#include "depth_first_search_solver.h"
#include <algorithm>
#include <iostream>

bool DepthFirstSearchSolver::DFS(int vertex, const Graph &adjacencyList, int endVertex)
{

    if (vertex == endVertex)
    {
        return true;
    }

    vector<int> neighbor_indices(adjacencyList[vertex].size());
    iota(neighbor_indices.begin(), neighbor_indices.end(), 0);
    shuffle(neighbor_indices.begin(), neighbor_indices.end(), generator_);

    for (auto index : neighbor_indices)
    {
        int nextVertex = get<0>(adjacencyList[vertex][index]);
        if (nextVertex < 0 || parent_[nextVertex] != -1)
            continue;
        parent_[nextVertex] = vertex;
        if (DFS(nextVertex, adjacencyList, endVertex))
        {
            return true;
        }
    }
    return false;
}

vector<int> DepthFirstSearchSolver::Solve(int width, int height,
                                          const Graph &adjacencyList,
                                          int startVertex,
                                          int endVertex)
{
    int vertices = width * height;
    parent_ = vector<int>(vertices, -1);
    parent_[startVertex] = startVertex;
    DFS(startVertex, adjacencyList, endVertex);
    return parent_;
}