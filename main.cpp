#include "depth_first_search.h"
#include "kruskal.h"
#include "loop_erased_random_walk.h"
#include "depth_first_search_solver.h"
#include "breadth_first_search_solver.h"
#include "a_star_solver.h"
#include "maze.h"
#include <cstring>
#include <iostream>
#include <map>
#include <string>
using namespace std;

void usage(ostream &out)
{
    out << "Usage:    mazegen   [--help] [-b <build algorithm type>]" << endl;
    out << "                    [-s solution algorithm type]" << endl;
    out << "                    [-w, -h <width>, <height>]" << endl;
    out << "                    [-o <output prefix>]" << endl;
    out << "                    [--show-solution]" << endl;

    out << endl;

    out << "Optional arguments:" << endl;
    out << "  --help            Show this help message and exit." << endl;
    out << "  -b                Algorithm Type for building the maze." << endl;
    out << "                      0: Loop Erased Random Walk (default)" << endl;
    out << "                      1: Kruskal's Algorithm" << endl;
    out << "                      2: Depth First Search" << endl;
    out << "  -s                Algorithm Type for solving the maze." << endl;
    out << "                      0: A* Search (default)" << endl;
    out << "                      1: Breadth First Search" << endl;
    out << "                      2: Depth First Search" << endl;
    out << "  -w, -h            Width and height (default - 20)" << endl;
    out << "  -o                Output prefix for .svg file (default - \"maze\")" << endl;
    out << "  --show-solution   Render the solution to the maze." << endl;
}

int main(int argc, char *argv[])
{
    string output_prefix = "result/maze";
    map<string, int> option_map{
        {"-b", 0}, {"-s", 0}, {"-w", 20}, {"-h", 20}, {"-o", 0}, {"--help", 0}, {"--show-solution", 0}};
    bool show_solution = false;

    for (int i = 1; i < argc; ++i)
    {
        if (option_map.find(argv[i]) == option_map.end())
        {
            cerr << "Unknown option: " << argv[i] << endl;
            usage(cerr);
            return 1;
        }
        if (argv[i] == string("--help"))
        {
            usage(cout);
            return 0;
        }
        if (argv[i] == string("--show-solution"))
        {
            show_solution = true;
            continue;
        }
        if (argv[i] == string("-o"))
        {
            if (++i < argc)
            {
                output_prefix = "result/" + string(argv[i]);
            }
            else
            {
                cerr << "Missing argument for -o option." << endl;
                usage(cerr);
                return 1;
            }
            continue;
        }
        if (i + 1 == argc)
        {
            cerr << "Missing argument for " << argv[i] << " option." << endl;
            usage(cerr);
            return 1;
        }
        int x;
        try
        {
            x = stoi(argv[i + 1]);
        }
        catch (...)
        {
            cerr << "Invalid argument " << argv[i + 1] << " for option "
                      << argv[i] << "\n";
            usage(cerr);
            return 1;
        }
        option_map[argv[i++]] = x;
    }

    Maze *maze;
    SpanningTreeAlgorithm *build_algorithm;

    if(option_map["-w"] <= 0 || option_map["-h"] <= 0) {
        cerr << "Width and height must be positive integers." << endl;
        usage(cerr);
        return 1;
    }

    cout << "Generating maze of size " << option_map["-w"] << "x" << option_map["-h"] << endl;
    maze = new Maze(option_map["-w"], option_map["-h"]);

    switch (option_map["-b"])
    {
    case 0:
        cout << "Using Loop Erased Random Walk to build the maze." << endl;
        build_algorithm = new LoopErasedRandomWalk();
        break;
    case 1:
        cout << "Using Kruskal's algorithm to build the maze." << endl;
        build_algorithm = new Kruskal();
        break;
    case 2:
        cout << "Using Depth First Search to build the maze." << endl;
        build_algorithm = new DepthFirstSearch();
        break;
    default:
        cerr << "Unknown algorithm type: " << option_map["-b"] << endl;
        usage(cerr);
        return 1;
    }
    maze->GenerateMaze(build_algorithm);

    maze->PrintMazeSVG(output_prefix, false);
    cout << "Rendering unsolved maze to '" << output_prefix << ".svg'..." << endl;

    if(show_solution)
    {
        SolverAlgorithm *solve_algorithm;

        switch (option_map["-s"])
        {
        case 0:
            cout << "Using A* Search to solve the maze." << endl;
            solve_algorithm = new AStarSolver();
            break;
        case 1:
            cout << "Using Breadth First Search to solve the maze." << endl;
            solve_algorithm = new BreadthFirstSearchSolver();
            break;
        case 2:
            cout << "Using Depth First Search to solve the maze." << endl;
            solve_algorithm = new DepthFirstSearchSolver();
            break;
        default:
            cout << "Unknown solver algorithm type: " << option_map["-s"] << ". Using A* Search." << endl;
            solve_algorithm = new AStarSolver();
            break;
        }
        maze->Solve(solve_algorithm);
        cout << "Rendering solved maze to '" << output_prefix << "_solved.svg'..." << endl;
        maze->PrintMazeSVG(output_prefix, true);
    }
    return 0;
}
