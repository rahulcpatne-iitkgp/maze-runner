#include "a_star_solver.h"
#include <algorithm>
#include <numeric>
#include <queue>
#include <cmath>

vector<int> AStarSolver::Solve(int width, int height,
                               const Graph &adjacencyList,
                               int startVertex,
                               int endVertex)
{
    int vertices = width * height;
    parent_ = vector<int>(vertices, -1);
    parent_[startVertex] = startVertex;

    auto compare = [](const pair<int, int> &a, const pair<int, int> &b)
    {
        return a.second > b.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> openSet(compare);

    int initialFScore = manhattanDistance(startVertex, endVertex, width);
    openSet.push({startVertex, initialFScore});

    vector<int> gScore(vertices, numeric_limits<int>::max());
    gScore[startVertex] = 0;

    while (!openSet.empty())
    {
        int current = openSet.top().first;
        openSet.pop();

        if (current == endVertex)
        {
            break;
        }

        vector<int> neighbor_indices(adjacencyList[current].size());
        iota(neighbor_indices.begin(), neighbor_indices.end(), 0);
        shuffle(neighbor_indices.begin(), neighbor_indices.end(), generator_);

        for (auto index : neighbor_indices)
        {
            int nextVertex = get<0>(adjacencyList[current][index]);
            if (nextVertex < 0)
                continue;

            int tentative_gScore = gScore[current] + 1;

            if (tentative_gScore < gScore[nextVertex])
            {

                parent_[nextVertex] = current;
                gScore[nextVertex] = tentative_gScore;

                int fScore = tentative_gScore + manhattanDistance(nextVertex, endVertex, width);

                openSet.push({nextVertex, fScore});
            }
        }
    }

    return parent_;
}

int AStarSolver::manhattanDistance(int vertex1, int vertex2, int width) const
{

    int x1 = vertex1 % width;
    int y1 = vertex1 / width;
    int x2 = vertex2 % width;
    int y2 = vertex2 / width;

    return std::abs(x1 - x2) + std::abs(y1 - y2);
}
