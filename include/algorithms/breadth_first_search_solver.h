#ifndef BREADTH_FIRST_SEARCH_SOLVER_H
#define BREADTH_FIRST_SEARCH_SOLVER_H

#include "solver_algorithm.h"
#include <queue>

class BreadthFirstSearchSolver : public SolverAlgorithm
{
public:
    vector<int> Solve(int width, int height, const Graph &adjacencyList,
                      int startVertex, int endVertex) override;

private:
    vector<int> parent_;
};

#endif // BREADTH_FIRST_SEARCH_SOLVER_H
