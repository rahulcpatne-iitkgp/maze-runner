#include "breadth_first_search_solver.h"
#include <algorithm>
#include <numeric>

vector<int> BreadthFirstSearchSolver::Solve(int width, int height,
                                            const Graph &adjacencyList,
                                            int startVertex,
                                            int endVertex)
{
    int vertices = width * height;
    parent_ = vector<int>(vertices, -1);
    parent_[startVertex] = startVertex;

    queue<int> q;
    q.push(startVertex);

    while (!q.empty())
    {
        int vertex = q.front();
        q.pop();

        if (vertex == endVertex)
        {
            break;
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
            q.push(nextVertex);
        }
    }

    return parent_;
}
