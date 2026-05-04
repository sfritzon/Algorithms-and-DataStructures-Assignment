# Algorithm Visualizer

A real-time algorithm visualizer built with **C++17** and **Raylib 5** on a Linux machine.
It visualizes sorting algorithms and pathfinding algorithms. You can navigate through the different visualizers with the main menu at start.

---

## Table of Contents

1. [Project Overview and Requirements](#1-project-overview-and-requirements)
2. [Features](#2-features)
3. [Controls](#3-controls)
4. [Project Structure](#4-project-structure)
5. [Architecture](#5-architecture)
6. [Building](#6-building)
7. [Dependencies](#7-dependencies)


## 1. Project Overview and Requirements
The assignment is to create a sorting visualizer that shows the progress of different sorting algorithms and a maze visualizer for pathfinding algorithms built with Raylib and C++.

For G:

    Create a sorting visualizer project
    Have at least 3 of the sorting algorithms available to visualize from the course material information (heap sort, bubble sort etc)
    Be able to swap between the scenes with a button press
    Bonus: Add information about comparisons and swaps made for the algorithm when it's completed

For VG:

    All of G and..
    Create a maze visualizer project that shows a pathfinding algorithm working its way through the start to the end of the maze
    Maze has to at least have a size of 25 x 25, and contain walls that block a portion of the path
    The maze needs to be solvable, no viable path = fail
    You have to implement at least 2 pathfinding algorithms from the course documentation ( BFS / DFS / Dijkstras / A* )
    Bonus: At the end when a path if found, simulate a mouse walking the path towards the end goal and finding its cheese!

## 2. Features

### Start Menu
- Arrow key navigation to select a visualizer
- ENTER to launch, ESC to return from any visualizer

### Sorting Visualizer
Step-by-step visualization of three sorting algorithms with live comparison and swap counters displayed on completion.

| Algorithm      | Complexity  | Description                                  |
|----------------|-------------|----------------------------------------------|
| Bubble Sort    | O(n²)       | Repeatedly bubbles the largest element to end |
| Insertion Sort | O(n²)       | Grows a sorted prefix one element at a time  |
| Heap Sort      | O(n log n)  | Builds a max-heap, extracts root n times     |

**Bar colours:**

| Colour | Purpose                     |
|--------|--------------------------------|
| Gray   | Default – untouched            |
| Yellow | Comparing – two bars examined  |
| Red    | Swapping – a swap in progress  |
| Green  | Sorted – in its final position |

### Maze Visualizer
A 25×25 maze is procedurally generated using **recursive backtracking**, guaranteeing a solvable path every time. Four pathfinding algorithms explore it step by step.

| Algorithm   | Frontier        | Finds shortest path? |
|-------------|-----------------|----------------------|
| BFS         | Queue (FIFO)    | Yes                  |
| DFS         | Stack (LIFO)    | No                   |
| A*          | Priority queue + Manhattan heuristic | Yes   |

**Cell colours:**

| Colour | Purpose              |
|--------|----------------------|
| Dark   | Wall                 |
| Gray   | Open – unvisited     |
| Blue   | Visited – explored   |
| Yellow | Frontier – queued    |
| Green  | Final solved path    |
| Red    | Start cell           |
| Orange | End cell             |

**Fun stuff:** When the path has been found a little mouse appears, follows the path and then finds the triangle cheese.

---

## 3. Controls

| Key        | Action                                      |
|------------|---------------------------------------------|
| `↑` / `↓` | Navigate menu / adjust speed                |
| `ENTER`    | Select in menu / cycle to next algorithm    |
| `R`        | Reset and reshuffle current algorithm       |
| `ESC`      | Return to main menu                         |

---

## 4. Project Structure

```
Algorithms-and-DataStructures-Assignment/
├── assets/
│   └── fonts/              # Optional custom fonts
├── src/
│   ├── main.cpp            # Window + game loop
│   ├── AppState.h          # Enum: Menu, Sorting, Maze
│   ├── AppManager.h        # Top-level state machine
│   ├── MenuScene.h         # Start screen
│   │
│   ├── BarArray.h          # Bar data + BarState enum
│   ├── SortScene.h         # Abstract sort base class
│   ├── SceneManager.h      # Manages sorting scenes
│   ├── BubbleSortScene.h
│   ├── InsertionSortScene.h
│   ├── HeapSortScene.h
│   │
│   ├── MazeGrid.h          # 25x25 grid + CellState enum
│   ├── PathScene.h         # Abstract pathfinding base class
│   ├── MazeManager.h       # Manages maze scenes
│   ├── BFSScene.h
│   ├── DFSScene.h
│   ├── AStarScene.h
│   └── MouseAnimator.h     # Bonus mouse animation
├── CMakeLists.txt
└── README.md
```

---

## 5. Architecture

The project uses a layered state machine design:

```
main.cpp
  └── AppManager          (owns everything, routes by AppState)
        ├── MenuScene     (start screen)
        ├── SceneManager  (sorting branch)
        │     └── SortScene* × 3
        └── MazeManager   (maze branch)
              ├── PathScene* × 3
              └── MouseAnimator
```

Each algorithm advances **one step per frame** so the visualization is always smooth and pauses via speed controls.

---

## 6. Building

- CMake
- C++ compiler
- Git
- Raylib 5

### Linux

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
./build/Algorithms-and-DataStructures-Assignment
```

### Windows

```cmd
cmake -B build
cmake --build build --config Release
.\build\Release\Algorithms-and-DataStructures-Assignment.exe
```

Raylib is automatically downloaded and compiled on first build if not found system-wide locally.

---

## 7. Dependencies

- [Raylib 5](https://github.com/raysan5/raylib) — graphics, input, window management
- C++ STL — `std::queue`, `std::stack`, `std::priority_queue`, `std::mt19937`
