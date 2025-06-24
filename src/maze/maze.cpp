#include "maze.h"
#include "depth_first_search.h"
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

Maze::Maze(int width, int height)
    : vertices_(width * height), width_(width), height_(height),
      startVertex_(0), endVertex_(width * height - 1) {}

int Maze::VertexIndex(int row, int col) const
{
    return row * width_ + col;
}

void Maze::InitialiseGraph()
{
    /*
        vertex index 0 is lower left corner
        Lower left corner left border is ENTRANCE to maze
        Top right corner right border is EXIT from maze
    */
    gridGraph_.clear();
    gridGraph_.resize(vertices_);

    for (int i = 0; i < width_; ++i)
    {
        gridGraph_[VertexIndex(0, i)].emplace_back(
            -1, make_shared<CellBorder>(i, 0, i + 1, 0));
        gridGraph_[VertexIndex(height_ - 1, i)].emplace_back(
            -1, make_shared<CellBorder>(i, height_, i + 1, height_));
    }

    for (int i = 0; i < height_; ++i)
    {
        if (i != 0)
            gridGraph_[VertexIndex(i, 0)].emplace_back(
                -1, make_shared<CellBorder>(0, i, 0, i + 1));
        if (i != height_ - 1)
            gridGraph_[VertexIndex(i, width_ - 1)].emplace_back(
                -1, make_shared<CellBorder>(width_, i, width_, i + 1));
    }

    for (int i = 0; i < height_; ++i)
    {
        for (int j = 0; j < width_ - 1; ++j)
        {
            shared_ptr<CellBorder> ptr = make_shared<CellBorder>(j + 1, i, j + 1, i + 1);

            gridGraph_[VertexIndex(i, j)].emplace_back(VertexIndex(i, j + 1), ptr);
            gridGraph_[VertexIndex(i, j + 1)].emplace_back(VertexIndex(i, j), ptr);
        }
    }

    for (int i = 0; i < height_ - 1; ++i)
    {
        for (int j = 0; j < width_; ++j)
        {
            shared_ptr<CellBorder> ptr = make_shared<CellBorder>(j, i + 1, j + 1, i + 1);

            gridGraph_[VertexIndex(i, j)].emplace_back(VertexIndex(i + 1, j), ptr);
            gridGraph_[VertexIndex(i + 1, j)].emplace_back(VertexIndex(i, j), ptr);
        }
    }
}

tuple<double, double, double, double> Maze::GetCoordinateBounds() const
{
    return make_tuple(0.0, 0.0, static_cast<double>(width_), static_cast<double>(height_));
}

void Maze::GenerateMaze(SpanningTreeAlgorithm *algorithm)
{
    InitialiseGraph();
    auto spanningTreeEdges = algorithm->SpanningTree(vertices_, gridGraph_);

    // Create the subset graph to be used in the solution
    spanningTreeGraph_ = Graph(vertices_);
    for (const auto &[u, v] : spanningTreeEdges)
    {
        // Find the corresponding edge in the grid
        spanningTreeGraph_[u].push_back(
            *find_if(gridGraph_[u].begin(), gridGraph_[u].end(),
                     [v = v](const Edge &e)
                     { return get<0>(e) == v; }));
        spanningTreeGraph_[v].push_back(
            *find_if(gridGraph_[v].begin(), gridGraph_[v].end(),
                     [u = u](const Edge &e)
                     { return get<0>(e) == u; }));
    }

    // Remove borders that are a part of the spanning tree
    RemoveBorders(spanningTreeEdges);
}

void Maze::Solve(SolverAlgorithm* algorithm)
{
    auto parent = algorithm->Solve(vertices_, spanningTreeGraph_, startVertex_);
    solutionGraph_ = Graph(vertices_);
    for (int u = endVertex_; parent[u] != u; u = parent[u])
    {
        solutionGraph_[u].push_back(*find_if(
            spanningTreeGraph_[u].begin(), spanningTreeGraph_[u].end(),
            [u, &parent](const Edge &e)
            { return get<0>(e) == parent[u]; }));
    }
}

void Maze::RemoveBorders(const vector<pair<int, int>> &edges)
{
    for (const auto &[u, v] : edges)
    {
        gridGraph_[u].erase(
            find_if(gridGraph_[u].begin(), gridGraph_[u].end(),
                    [v = v](const Edge &e)
                    { return get<0>(e) == v; }));
        gridGraph_[v].erase(
            find_if(gridGraph_[v].begin(), gridGraph_[v].end(),
                    [u = u](const Edge &e)
                    { return get<0>(e) == u; }));
    }
}

void Maze::PrintMazeSVG(const string &outputprefix, bool showSolution) const
{
    ofstream svgfile;
    if (showSolution)
        svgfile.open(outputprefix + "_solved.svg");
    else
        svgfile.open(outputprefix + ".svg");

    if (!svgfile)
    {
        cerr << "Error opening " << outputprefix << ".svg for writing.\n";
        cerr << "Terminating.";
        exit(1);
    }

    double xmin, ymin, xmax, ymax;
    tie(xmin, ymin, xmax, ymax) = GetCoordinateBounds();
    int xresolution = (xmax - xmin + 2) * 30,
        yresolution = (ymax - ymin + 2) * 30;

    svgfile << "<svg width=\"" << xresolution << "\" height=\"" << yresolution
            << "\" xmlns=\"http://www.w3.org/2000/svg\">" << endl;
    svgfile << "<g transform=\"translate(" << (1 - xmin) * 30 << ","
            << yresolution - (1 - ymin) * 30 << ") scale(1,-1)\">" << endl;
    svgfile << "<rect x=\"" << (xmin - 1) * 30 << "\" y=\"" << (ymin - 1) * 30
            << "\" width=\"" << xresolution << "\" height=\"" << yresolution
            << "\" fill=\"white\"/>" << endl;

    // Draw maze walls
    for (int i = 0; i < vertices_; ++i)
    {
        for (const auto &edge : gridGraph_[i])
        {
            if (get<0>(edge) < i)
            {
                svgfile << get<1>(edge)->PrintStringSVG("black") << "\n";
            }
        }
    }

    // Draw solution path if requested
    if (showSolution)
    {
        svgfile << "<!-- Solution Path -->\n";

        // Draw red lines connecting cell centers along the solution path
        for (int v = 0; v < vertices_; v++)
        {
            for (const auto &edge : solutionGraph_[v])
            {
                auto border = get<1>(edge);

                shared_ptr<LineSegment> solutionLine = make_shared<LineSegment>(border->GetCellCenters());
                svgfile << solutionLine->PrintStringSVG("red") << "\n";
            }
        }
    }

    svgfile << "</g>" << endl;
    svgfile << "</svg>" << endl;
}