#ifndef DEPTH_FIRST_SEARCH_SOLVER_H
#define DEPTH_FIRST_SEARCH_SOLVER_H

#include "solver_algorithm.h"

class DepthFirstSearchSolver : public SolverAlgorithm {
public:
    vector<int> Solve(int, const Graph&, int) override;
    
private:
    vector<int> parent_, spanningTree_;
    void DFS(int, const Graph&);
};

#endif // DEPTH_FIRST_SEARCH_SOLVER_H