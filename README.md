# Algorithm Visualizer

A real-time algorithm visualizer built with **C++17** and **Raylib 5** on a Linux machine.
It visualizes sorting algorithms and pathfinding algorithms. You can navigate through the different visualizers with the main menu at start.

---

## Features

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

| Colour | Meaning                        |
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
| Dijkstra    | Priority queue  | Yes                  |
| A*          | Priority queue + Manhattan heuristic | Yes   |

**Cell colours:**

| Colour | Meaning              |
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

## Controls

| Key        | Action                                      |
|------------|---------------------------------------------|
| `↑` / `↓` | Navigate menu / adjust speed                |
| `ENTER`    | Select in menu / cycle to next algorithm    |
| `R`        | Reset and reshuffle current algorithm       |
| `ESC`      | Return to main menu                         |

---

## Project Structure

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
│   ├── DijkstraScene.h
│   ├── AStarScene.h
│   └── MouseAnimator.h     # Bonus mouse animation
├── CMakeLists.txt
└── README.md
```

---

## Architecture

The project uses a layered state machine design:

```
main.cpp
  └── AppManager          (owns everything, routes by AppState)
        ├── MenuScene     (start screen)
        ├── SceneManager  (sorting branch)
        │     └── SortScene* × 3
        └── MazeManager   (maze branch)
              ├── PathScene* × 4
              └── MouseAnimator
```

Each algorithm advances **one step per frame** so the visualization is always smooth and pauses via speed controls.

---

## Building

- CMake
- C++17 compiler
- Git
- Raylib 5

### Linux

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)
./build/Algorithms-and-DataStructures-Assignment
```

Raylib is automatically downloaded and compiled on first build if not found system-wide locally.

---

## Dependencies

- [Raylib 5](https://github.com/raysan5/raylib) — graphics, input, window management
- C++ STL — `std::queue`, `std::stack`, `std::priority_queue`, `std::mt19937`
