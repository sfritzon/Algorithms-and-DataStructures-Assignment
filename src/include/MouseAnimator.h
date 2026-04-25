#pragma once
#include <vector>
#include "MazeGrid.h"
#include "raylib.h"


class MouseAnimator 
{
    public:
    void Start(const std::vector<std::pair<int,int>>& solvedPath) 
    {
        path = solvedPath;
        pathIndex = 0;
        active = true;
        done = false;
        frameTimer = 0.0f;
    }


    void Reset() 
    {
        active = false;
        done = false;
        pathIndex = 0;
        path.clear();
    }


    bool IsActive() const 
    { 
        return active; 
    }


    bool IsDone() const 
    { 
        return done;   
    }


    void Update(float dt) 
    {
        if (!active || done) return;
        frameTimer += dt;

        if (frameTimer >= STEP_TIME) 
        {
            frameTimer = 0.0f;
            ++pathIndex;

            if (pathIndex >= (int)path.size()) 
            {
                pathIndex = (int)path.size() - 1;
                done = true;
            }
        }
    }


    void Draw(int x, int y, int w, int h) const 
    {
        if (!active || path.empty()) return;

        float cw = (float)w / MazeGrid::COLS;
        float ch = (float)h / MazeGrid::ROWS;

        // Draw mouse body at current cell
        auto [r, c] = path[pathIndex];
        float mx = x + c * cw + cw * 0.5f;
        float my = y + r * ch + ch * 0.5f;
        float radius = std::min(cw, ch) * 0.38f;

        // Body
        DrawCircle((int)mx, (int)my, radius, {220, 220, 230, 255});

        // Eyes
        DrawCircle((int)(mx + radius*0.3f), (int)(my - radius*0.2f), radius*0.18f, { 30, 30, 30, 255 });

        // Ear
        DrawCircle((int)(mx - radius*0.3f), (int)(my - radius*0.6f), radius*0.25f, { 255, 180, 190, 255 });

        // Cheese at the end cell
        if (done) 
        {
            auto [er, ec] = path.back();
            float ex = x + ec * cw + cw * 0.5f;
            float ey = y + er * ch + ch * 0.5f;

            // Simple yellow triangle = cheese wedge
            DrawTriangle(
                { ex - cw*0.4f, ey + ch*0.35f },
                { ex + cw*0.4f, ey + ch*0.35f },
                { ex, ey - ch*0.35f},
                { 255, 210, 50, 255 }
            );

            // Holes
            DrawCircle((int)ex, (int)(ey + ch*0.1f), std::min(cw,ch)*0.08f, { 200, 160, 30, 255 });
        }
    }

    private:
    std::vector<std::pair<int,int>> path;
    int pathIndex  = 0;
    bool active = false;
    bool done = false;
    float frameTimer = 0.0f;

    static constexpr float STEP_TIME = 0.07f; // Seconds per cell
};
