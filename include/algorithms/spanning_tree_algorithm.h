#ifndef SPANNING_TREE_ALGORITHM_H
#define SPANNING_TREE_ALGORITHM_H

#include "cell_border.h"
#include <memory>
#include <random>
#include <vector>
using namespace std;

typedef tuple<int, shared_ptr<CellBorder>> Edge;
typedef vector<vector<Edge>> Graph;

class SpanningTreeAlgorithm {
public:
    SpanningTreeAlgorithm();
    virtual vector<pair<int, int>> SpanningTree(int, const Graph&) = 0;

protected:
    vector<pair<int, int>> spanningTree_;
    random_device randomDevice_;
    mt19937 generator_;
};

#endif