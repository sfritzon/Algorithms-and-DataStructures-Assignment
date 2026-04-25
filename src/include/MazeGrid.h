#pragma once
#include <vector>
#include <stack>
#include <random>
#include <functional>
#include "raylib.h"


enum class CellState
{
    Wall,           // Dark
    Open,           // Gray
    Visited,        // Blue
    Frontier,       // Yellow
    Path            // Green
};


class MazeGrid
{
    public:
    static constexpr int COLS = 25;
    static constexpr int ROWS = 25;

    static constexpr Color COL_WALL = { 24, 24, 32, 255 };
    static constexpr Color COL_OPEN = { 80, 80, 90, 255 };
    static constexpr Color COL_VISITED = { 50, 120, 200, 255 };
    static constexpr Color COL_FRONTIER = { 255, 210, 50, 255 };
    static constexpr Color COL_PATH = { 60, 200, 100, 255 };
    static constexpr Color COL_START = { 220, 60, 60, 255 };
    static constexpr Color COL_END = { 220, 160, 40, 255 };

    MazeGrid()
    {
        Generate();
    }


    void Generate()
    {
        for (int r = 0; r < ROWS; ++r)
            for (int c = 0; c < COLS; ++c)
            {
                cells[r][c] = CellState::Wall;
            }

        static std::mt19937 randNumGen{ std::random_device{}()};
        std::vector<std::pair<int, int>> stack;

        auto carve = [&](int r, int c)
        {
            cells[r][c] = CellState::Open;
            stack.push_back({r, c});
            
            while (!stack.empty())
            {
                auto [cr, cc] = stack.back();

                std::vector<std::pair<int, int >> neighbors;

                for (auto [dr, dc] : std::initializer_list<std::pair<int, int>> { {-2,0},{2,0},{0,-2},{0,2} })
                {
                    int nr = cr + dr, nc = cc + dc;
                    if (nr > 0 && nr < ROWS - 1 && nc > 0 && nc < COLS - 1 && cells[nr][nc] == CellState::Wall) neighbors.push_back({nr, nc});
                }

                if (neighbors.empty())
                {
                    stack.pop_back();
                }
                else
                {
                    auto [nr, nc] = neighbors[randNumGen() % neighbors.size()];

                    cells[(cr+nr)/2][(cc+nc)/2] = CellState::Open;
                    cells[nr][nc] = CellState::Open;
                    stack.push_back({nr, nc});
                }
            }
        };

        carve(1, 1);

        cells[0][1] = CellState::Open;
        cells[ROWS - 1][COLS - 2] = CellState::Open;
    }


    void ResetStates()
    {
        for (int r = 0; r < ROWS; ++r)
            for (int c = 0; c < COLS; ++c)
                if (cells[r][c] != CellState::Wall)
                    cells[r][c] = CellState::Open;
    }


    CellState Get(int r, int c) const 
    { 
        return cells[r][c]; 
    }
    
        
    void Set(int r, int c, CellState s) 
    { 
        cells[r][c] = s; 
    }


    bool IsWall(int r, int c) const 
    { 
        return cells[r][c] == CellState::Wall; 
    }
    
    
    bool InBounds(int r, int c) const 
    {
        return r >= 0 && r < ROWS && c >= 0 && c < COLS;
    }


    std::pair<int,int> StartCell() const 
    { 
        return {0, 1}; 
    }


    std::pair<int,int> EndCell() const 
    { 
        return {ROWS-1, COLS-2}; 
    }


    void Draw(int x, int y, int w, int h) const 
    {
        float cw = (float)w / COLS;
        float ch = (float)h / ROWS;

        for (int r = 0; r < ROWS; ++r) 
        {
            for (int c = 0; c < COLS; ++c) 
            {
                float bx = x + c * cw;
                float by = y + r * ch;

                Color col;
                switch (cells[r][c]) {
                    case CellState::Visited: 
                        col = COL_VISITED;  
                        break;

                    case CellState::Frontier: 
                        col = COL_FRONTIER; 
                        break;

                    case CellState::Path:
                        col = COL_PATH;
                        break;
                    
                    case CellState::Open:
                        col = COL_OPEN;
                        break;

                    default:
                        col = COL_WALL;
                        break;
                }

                DrawRectangleRec({bx, by, cw, ch}, col);
            }
        }

        auto [sr, sc] = StartCell();
        auto [er, ec] = EndCell();
        
        DrawRectangleRec({x + sc*cw, y + sr*ch, cw, ch}, COL_START);
        DrawRectangleRec({x + ec*cw, y + er*ch, cw, ch}, COL_END);
    }


    private:
    CellState cells[ROWS][COLS];
};
