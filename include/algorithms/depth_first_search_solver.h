#ifndef DEPTH_FIRST_SEARCH_SOLVER_H
#define DEPTH_FIRST_SEARCH_SOLVER_H

#include "solver_algorithm.h"

class DepthFirstSearchSolver : public SolverAlgorithm
{
public:
    vector<int> Solve(int width, int height, const Graph &adjacencyList,
                      int startVertex, int endVertex) override;

private:
    vector<int> parent_;
    bool DFS(int vertex, const Graph &adjacencyList, int endVertex);
};

#endif // DEPTH_FIRST_SEARCH_SOLVER_H