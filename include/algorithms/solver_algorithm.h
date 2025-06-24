#ifndef SOLVER_ALGORITHM_H
#define SOLVER_ALGORITHM_H

#include "defs.h"
#include <random>
#include <vector>

class SolverAlgorithm {
public:
    inline SolverAlgorithm() : generator_(randomDevice_()) {}
    virtual vector<int> Solve(int vertices,
                              const Graph &adjacencyList,
                              int startVertex) = 0;
protected:
    random_device randomDevice_;
    mt19937 generator_;

};
#endif // SOLVER_ALGORITHM_H