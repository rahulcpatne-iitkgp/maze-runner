#ifndef MAZE_H
#define MAZE_H

#include "cell_border.h"
#include "spanning_tree_algorithm.h"
#include <memory>
#include <vector>

class Maze {
public:
    Maze(int = 20, int = 20);
    void GenerateMaze(SpanningTreeAlgorithm*);
    void PrintMazeSVG(const string&, bool = false) const;
    int GetVertexCount() const { return vertices_; }
    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }
    const Graph& GetAdjacencyList() const { return gridGraph_; }
    void InitialiseGraph();
    void Solve();

private:
    int vertices_, width_, height_;
    Graph gridGraph_, spanningTreeGraph_, solutionGraph_;
    int startVertex_, endVertex_;

    int VertexIndex(int, int) const;
    void RemoveBorders(const vector<pair<int, int>>&);
    tuple<double, double, double, double> GetCoordinateBounds() const;
};

#endif