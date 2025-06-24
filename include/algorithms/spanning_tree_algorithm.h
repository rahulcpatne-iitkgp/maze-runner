#ifndef SPANNING_TREE_ALGORITHM_H
#define SPANNING_TREE_ALGORITHM_H

#include "cell_border.h"
#include "defs.h"
#include <random>
#include <vector>
using namespace std;

class SpanningTreeAlgorithm
{
public:
    inline SpanningTreeAlgorithm() : generator_(randomDevice_()) {}
    virtual vector<pair<int, int>> SpanningTree(int, const Graph &) = 0;

protected:
    vector<pair<int, int>> spanningTree_;
    random_device randomDevice_;
    mt19937 generator_;
};

#endif // SPANNING_TREE_ALGORITHM_H