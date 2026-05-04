#pragma once
#include <stack>
#include <vector>
#include "PathScene.h"


class DFSPath : public PathScene {
public:
    DFSPath() : PathScene("DFS (Depth-First)") { OnReset(); }


    void OnReset() override 
    {
        while (!frontier.empty())
            frontier.pop();

        parent.assign(MazeGrid::ROWS, std::vector<std::pair<int,int>>(MazeGrid::COLS, {-1,-1}));

        auto [sr, sc] = maze.StartCell();
        frontier.push({sr, sc});
        maze.Set(sr, sc, CellState::Frontier);
        parent[sr][sc] = {sr, sc};
    }


    void Step() override 
    {
        if (solved || failed || frontier.empty()) 
        {
            if (frontier.empty() && !solved) failed = true;

            return;
        }

        auto [r, c] = frontier.top();
        frontier.pop();
        steps++;

        if (maze.Get(r, c) == CellState::Visited)
            return;

        if (std::make_pair(r,c) == maze.EndCell()) 
        {
            TracePath(parent, {r, c});
            solved = true;

            return;
        }

        maze.Set(r, c, CellState::Visited);

        for (auto [dr, dc] : DIRS) 
        {
            int nr = r+dr, nc = c+dc;
            if (maze.InBounds(nr, nc) && !maze.IsWall(nr, nc) && maze.Get(nr, nc) == CellState::Open) 
            {
                maze.Set(nr, nc, CellState::Frontier);
                parent[nr][nc] = {r, c};
                frontier.push({nr, nc});
            }
        }
    }


private:
    std::stack<std::pair<int,int>> frontier;
    std::vector<std::vector<std::pair<int,int>>> parent;

    static constexpr std::pair<int,int> DIRS[4] = {{ -1,0},{1,0},{0,-1},{0,1 }};
};
