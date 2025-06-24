#ifndef DEPTH_FIRST_SEARCH_H
#define DEPTH_FIRST_SEARCH_H

#include "spanning_tree_algorithm.h"
#include <vector>

class DepthFirstSearch : public SpanningTreeAlgorithm
{
public:
    vector<pair<int, int>> SpanningTree(int, const Graph &) override;

private:
    vector<int> parent_;
    void DFS(int, const Graph &);
};

#endif // DEPTH_FIRST_SEARCH_H