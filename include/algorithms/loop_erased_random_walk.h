#ifndef LOOP_ERASED_RANDOM_WALK_H
#define LOOP_ERASED_RANDOM_WALK_H
#include "spanning_tree_algorithm.h"
#include <vector>

class LoopErasedRandomWalk : public SpanningTreeAlgorithm {
public:
    vector<pair<int, int>> SpanningTree(int , const Graph&);

private:
    vector<int> visited_;
    void LERW(int, int, const Graph&);
};

#endif // LOOP_ERASED_RANDOM_WALK_H