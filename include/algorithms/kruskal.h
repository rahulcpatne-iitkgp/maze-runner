#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "spanning_tree_algorithm.h"
#include <vector>
#include <random>

class Kruskal : public SpanningTreeAlgorithm {
public:
    vector<pair<int, int>> SpanningTree(int, const Graph&) override;
    
private:
    vector<int> parent_;
    vector<int> rank_;

    int Find(int x);
    bool Union(int x, int y);
};

#endif