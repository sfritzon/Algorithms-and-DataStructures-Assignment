#pragma once
#include <queue>
#include <vector>
#include <climits>
#include <cmath>
#include "PathScene.h"


class AStarPath : public PathScene 
{
    public:
    AStarPath() : PathScene("A* Search") { OnReset(); }

    void OnReset() override 
    {
        while (!frontier.empty()) frontier.pop(); parent.assign(MazeGrid::ROWS, std::vector<std::pair<int,int>>(MazeGrid::COLS, {-1,-1}));

        gCost.assign(MazeGrid::ROWS, std::vector<int>(MazeGrid::COLS, INT_MAX));

        auto [sr, sc] = maze.StartCell();
        auto [er, ec] = maze.EndCell();
        gCost[sr][sc] = 0;
        int h = std::abs(er - sr) + std::abs(ec - sc);
        frontier.push({h, 0, sr, sc});
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

        auto [f, g, r, c] = frontier.top();
        frontier.pop();
        ++steps;

        if (g > gCost[r][c]) return;

        if (std::make_pair(r,c) == maze.EndCell()) 
        {
            TracePath(parent, {r, c});
            solved = true;
            return;
        }

        maze.Set(r, c, CellState::Visited);

        auto [er, ec] = maze.EndCell();

        for (auto [dr, dc] : DIRS) 
        {
            int nr = r+dr, nc = c+dc;
            if (!maze.InBounds(nr, nc) || maze.IsWall(nr, nc)) continue;
            auto s = maze.Get(nr, nc);
            if (s == CellState::Visited) continue;

            int ng = g + 1;
            if (ng < gCost[nr][nc]) 
            {
                gCost[nr][nc] = ng;
                parent[nr][nc] = {r, c};
                int h = std::abs(er - nr) + std::abs(ec - nc);
                maze.Set(nr, nc, CellState::Frontier);
                frontier.push({ng + h, ng, nr, nc});
            }
        }
    }

private:
    using Entry = std::tuple<int,int,int,int>;
    std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> frontier;
    std::vector<std::vector<std::pair<int,int>>> parent;
    std::vector<std::vector<int>> gCost;

    static constexpr std::pair<int,int> DIRS[4] = {{ -1,0},{1,0},{0,-1},{0,1 }};
};
