#pragma once
#include <string>
#include <vector>
#include "MazeGrid.h"
#include "raylib.h"
#include <algorithm>


class PathScene 
{
    public:
    PathScene(const std::string& name) : name(name) {}

    virtual ~PathScene() = default;

    virtual void Step() = 0;

    virtual void Draw(int x, int y, int w, int h) 
    {
        maze.Draw(x, y, w, h);
    }


    virtual void Reset() 
    {
        maze.ResetStates();
        solved = false;
        failed = false;
        steps = 0;
        path.clear();
        OnReset();
    }


    virtual void OnReset() = 0;

    
    const std::string& GetName() const 
    { 
        return name; 
    }
    

    bool IsSolved()  const 
    { 
        return solved; 
    }
    

    bool IsFailed() const 
    { 
        return failed; 
    }
    

    int GetSteps() const 
    { 
        return steps; 
    }
    

    const std::vector<std::pair<int,int>>& GetPath() const 
    { 
        return path; 
    }


    MazeGrid& GetMaze()
    { 
        return maze; 
    }


    void DrawStats(int x, int y) const 
    {
	if (!solved && !failed)
	    return;

        DrawRectangle(x, y, 310, 70, { 10, 10, 18, 200 });
        DrawRectangleLines(x, y, 310, 70, { 80, 80, 100, 200 });
        DrawText(("Algorithm : " + name).c_str(), x+12, y+10, 16, { 180,180,200,255 });
        DrawText(("Steps: " + std::to_string(steps)).c_str(), x+12, y+32, 16, MazeGrid::COL_FRONTIER);

        if (solved) 
        {
            std::string pl = "Path len : " + std::to_string((int)path.size());
            DrawText(pl.c_str(), x+12, y+52, 16, MazeGrid::COL_PATH);
        } 
        else 
        {
            DrawText("No path found!", x+12, y+52, 16, { 220,60,60,255 });
        }
    }


protected:
    std::string name;
    MazeGrid maze;
    bool solved = false;
    bool failed = false;
    int steps = 0;
    std::vector<std::pair<int,int>> path;


    void TracePath(std::vector<std::vector<std::pair<int,int>>>& parent, std::pair<int,int> end) 
    {
        auto [er, ec] = end;
        auto [sr, sc] = maze.StartCell();
        auto cur = end;

        while (cur != maze.StartCell()) 
        {
            path.push_back(cur);
            cur = parent[cur.first][cur.second];
        }

        path.push_back(maze.StartCell());
        std::reverse(path.begin(), path.end());

        for (auto [r, c] : path)
            if (maze.Get(r, c) != CellState::Wall)
                maze.Set(r, c, CellState::Path);
    }
};
