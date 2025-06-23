#include "kruskal.h"
#include <algorithm>
#include <numeric>
#include <random>

vector<pair<int, int>> Kruskal::SpanningTree(int vertices,
                                             const Graph &adjacencyList)
{
    vector<pair<int, int>> edges;
    for (int i = 0; i < vertices; ++i)
    {
        for (const auto &edge : adjacencyList[i])
        {
            if (get<0>(edge) > i)
                edges.emplace_back(i, get<0>(edge));
        }
    }
    shuffle(edges.begin(), edges.end(), generator_);

    parent_ = vector<int>(vertices);
    rank_ = vector<int>(vertices, 0);  // Add rank array
    iota(parent_.begin(), parent_.end(), 0);

    spanningTree_.clear();
    for (const auto& edge : edges)
    {
        int u = edge.first;
        int v = edge.second;

        if (Union(u, v))  // Use optimized union function
        {
            spanningTree_.emplace_back(u, v);
        }
    }
    return spanningTree_;
}

int Kruskal::Find(int x)
{
    if (parent_[x] != x)
        parent_[x] = Find(parent_[x]);
    return parent_[x];
}

bool Kruskal::Union(int x, int y)
{
    int rootX = Find(x);
    int rootY = Find(y);
    
    if (rootX == rootY)
        return false;
    
    // Union by rank
    if (rank_[rootX] < rank_[rootY])
        parent_[rootX] = rootY;
    else if (rank_[rootX] > rank_[rootY])
        parent_[rootY] = rootX;
    else
    {
        parent_[rootY] = rootX;
        rank_[rootX]++;
    }
    return true;
}