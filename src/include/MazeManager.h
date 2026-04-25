#pragma once
#include <vector>
#include <string>
#include "PathScene.h"
#include "MouseAnimator.h"
#include "raylib.h"


class MazeManager 
{
    public:
    MazeManager() {}

    ~MazeManager() 
    { 
        for (auto* s : scenes) delete s; 
    }


    void AddScene(PathScene* scene) 
    { 
        scenes.push_back(scene); 
    }


    void Update(float dt) 
    {
        if (scenes.empty()) return;
        PathScene* cur = scenes[currentIndex];

        if (!cur->IsSolved() && !cur->IsFailed()) 
        {
            for (int s = 0; s < stepsPerFrame; ++s)
            {
                cur->Step();
            }
        } 
        else if (cur->IsSolved() && !mouse.IsActive()) 
        {
            mouse.Start(cur->GetPath());
        }

        mouse.Update(dt);
    }


    void Draw(int screenW, int screenH) 
    {
        if (scenes.empty()) return;

        const int HUD_H = 60;
        const int MARGIN = 20;
        const int MAZE_Y = HUD_H + MARGIN;
        const int MAZE_H = screenH - MAZE_Y - MARGIN;

        int side = std::min(screenW - MARGIN * 2, MAZE_H);
        int MAZE_X = (screenW - side) / 2;

        PathScene* cur = scenes[currentIndex];
        cur->Draw(MAZE_X, MAZE_Y, side, side);
        mouse.Draw(MAZE_X, MAZE_Y, side, side);
        cur->DrawStats(MARGIN, screenH - 90);
        DrawHUD(screenW);
    }


    void NextScene() 
    {
        if (scenes.empty()) return;
        currentIndex = (currentIndex + 1) % (int)scenes.size();
        scenes[currentIndex]->Reset();
        mouse.Reset();
    }


    void ResetCurrent() 
    {
        if (!scenes.empty()) scenes[currentIndex]->Reset();
        mouse.Reset();
    }


    void IncreaseSpeed() 
    { 
        stepsPerFrame = std::min(stepsPerFrame * 2, 64); 
    }


    void DecreaseSpeed() 
    { 
        stepsPerFrame = std::max(stepsPerFrame / 2, 1);  
    }


    int  GetStepsPerFrame() const 
    { 
        return stepsPerFrame; 
    }

private:
    std::vector<PathScene*> scenes;
    int currentIndex = 0;
    int stepsPerFrame = 1;
    MouseAnimator mouse;

    void DrawHUD(int screenW) 
    {
        DrawRectangle(0, 0, screenW, 52, { 12, 12, 20, 240 });
        DrawLine(0, 52, screenW, 52, { 60, 60, 80, 180 });
        if (scenes.empty()) return;

        PathScene* cur = scenes[currentIndex];

        // Algorithm name
        DrawText(cur->GetName().c_str(), 16, 14, 22, WHITE);

        // Scene dots
        int dotX = screenW / 2 - (int)scenes.size() * 18 / 2;

        for (int k = 0; k < (int)scenes.size(); ++k) 
        {
            Color dc = (k == currentIndex) ? WHITE : Color{ 80,80,100,255 };
            DrawCircle(dotX + k*20, 26, 5, dc);
        }

        // Controls hint
        const char* hint = "[ENTER] Next  [R] Reset  [UP/DN] Speed  [ESC] Menu";
        int hw = MeasureText(hint, 13);
        DrawText(hint, screenW - hw - 16, 20, 13, { 130,130,150,255 });

        // Speed
        std::string spd = "Speed: " + std::to_string(stepsPerFrame) + "x";
        DrawText(spd.c_str(), 16, 38, 12, { 100,100,130,255 });

        // Status badge
        if (cur->IsSolved()) 
        {
            const char* lbl = mouse.IsDone() ? "FOUND CHEESE!" : "PATH FOUND";
            Color bc = mouse.IsDone() ? MazeGrid::COL_END : MazeGrid::COL_PATH;

            int textWidth = MeasureText(lbl, 16);
            
            DrawRectangle(screenW/2 - textWidth/2 - 10, 14, textWidth+20, 24, bc);
            DrawText(lbl, screenW/2 - textWidth/2, 18, 16, BLACK);
        } 
        else if (cur->IsFailed()) 
        {
            const char* lbl = "NO PATH!";
            int textWidth = MeasureText(lbl, 16);
            DrawRectangle(screenW/2 - textWidth/2 - 10, 14, textWidth+20, 24, {220,60,60,255});
            DrawText(lbl, screenW/2 - textWidth/2, 18, 16, WHITE);
        }
    }
};
