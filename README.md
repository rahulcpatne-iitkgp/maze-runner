# 🧩 Maze Runner

A command-line tool for generating and solving mazes, inspired by [razimantv/mazegenerator](https://github.com/razimantv/mazegenerator), with **maze solving** and **solution visualization** features added!

---

## ✨ Features

- Generate **rectangular mazes** of any integer width and height.
- Choose from multiple algorithms for both **generation** and **solution**.
- Output clean `.svg` files — with or without solution paths — to visually analyze algorithm behavior.

---

## 🧱 Maze Generation Algorithms

Each algorithm creates a maze with unique structural characteristics:

- **Loop-Erased Random Walk (LERW)** (default)
    - Sparse, clean structure with few branches
- **Kruskal’s Algorithm**
    - Highly branched, dense and bushy paths
- **Depth First Search (DFS)**
    - Long winding paths, few junctions
  
---

## 🧭 Maze Solving Algorithms

Enable maze solving using `--show-solution`. Supported solving strategies:

- **A\*** (default)  
  - Uses **Manhattan distance** as a heuristic  
  - Generally finds shortest paths efficiently
- **Breadth First Search (BFS)**  
  - Finds shortest path  
  - Explores evenly in all directions  
- **Depth First Search (DFS)**  
  - May not find the shortest path  
  - Explores deep before wide

Select using `-s` option with values `0`, `1`, or `2`.

---

## 🖼️ Output

- Without `--show-solution`:  
  - ✅ One `.svg` file showing the **generated maze**

- With `--show-solution`:  
  - ✅ One `.svg` file with **just the maze**  
  - ✅ One `.svg` file with:
    - **Blue path** = Final solution path
    - **Light purple** = All nodes visited during search  
    *(Great for comparing how different algorithms explore the maze)*

---

## 🔧 Usage

In the root directory:

```bash
make
./mazegen --help
```

### Command Syntax:

```bash
Usage:    mazegen   [--help] [-b <build algorithm type>]
                    [-s <solution algorithm type>]
                    [-w <width>] [-h <height>]
                    [-o <output prefix>]
                    [--show-solution]
```

### Optional Arguments:

- `--help`  
  Show this help message and exit.

- `-b <int>`  
  Maze generation algorithm (default: 0)  
  - `0`: Loop Erased Random Walk  
  - `1`: Kruskal's Algorithm  
  - `2`: Depth First Search

- `-s <int>`  
  Maze solving algorithm (default: 0)  
  - `0`: A\* Search  
  - `1`: Breadth First Search  
  - `2`: Depth First Search

- `-w <int>` `-h <int>`  
  Width and height of the maze (default: 20)

- `-o <string>`  
  Output prefix for the `.svg` file(s) (default: `maze`)

- `--show-solution`  
  Also generate the solved maze output

---

## 🔍 Example

```bash
./mazegen -w 40 -h 40 -b 2 -s 0 -o dfs_a_star --show-solution
```

Generates a 40×40 maze using **DFS**, solves it using **A\***, and creates two `.svg` files:
- `dfs_a_star.svg` (maze only)
- `dfs_a_star_solved.svg` (solution overlay)

---

Happy maze running! 🏃‍♂️🌀
