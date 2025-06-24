#ifndef DEFS_H
#define DEFS_H

#include "cell_border.h"
#include <memory>
#include <tuple>
#include <vector>
typedef tuple<int, shared_ptr<CellBorder>> Edge;
typedef vector<vector<Edge>> Graph;

#endif // DEFS_H