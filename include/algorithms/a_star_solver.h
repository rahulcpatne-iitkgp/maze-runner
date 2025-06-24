#ifndef A_STAR_SOLVER_H
#define A_STAR_SOLVER_H

#include "solver_algorithm.h"
#include <queue>
#include <limits>

class AStarSolver : public SolverAlgorithm
{
public:
    vector<int> Solve(int width, int height, const Graph &adjacencyList,
                      int startVertex, int endVertex) override;

private:
    vector<int> parent_;
    int manhattanDistance(int, int, int) const;
};

#endif // A_STAR_SOLVER_H
