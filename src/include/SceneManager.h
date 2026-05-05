#pragma once
#include <vector>
#include <string>
#include "SortScene.h"
#include "raylib.h"


class SceneManager
{
    public:
    SceneManager() : currentIndex(0) {}

    ~SceneManager() 
    {
        for (auto* s : scenes) delete s;
    }
    
    
    void AddScene(SortScene* scene) 
    {
        scenes.push_back(scene);
    }


    void Update() 
    {
        if (scenes.empty())
            return;

        scenes[currentIndex]->Update();
    }


    void Draw(int screenW, int screenH) 
    {
        if (scenes.empty())
            return;

        const int HUD_H = 60;
        const int MARGIN = 20;
        const int BAR_AREA_Y = HUD_H + MARGIN;
        const int BAR_AREA_H = screenH - BAR_AREA_Y - MARGIN;

        scenes[currentIndex]->Draw(MARGIN, BAR_AREA_Y, screenW - MARGIN * 2, BAR_AREA_H);
        scenes[currentIndex]->DrawStats(MARGIN, screenH - 110);
        DrawHUD(screenW);
    }


    void NextScene() 
    {
        if (scenes.empty())
            return;

        currentIndex = (currentIndex + 1) % (int)scenes.size(); 
        scenes[currentIndex]->Reset();
    }


    void ResetCurrent() 
    {
        if (!scenes.empty())
            scenes[currentIndex]->Reset();
    }


    int  GetStepsPerFrame()  const 
    { 
        return stepsPerFrame; 
    }


    void IncreaseSpeed()
    { 
        stepsPerFrame = std::min(stepsPerFrame * 2, 512); 
    }


    void DecreaseSpeed()
    { 
        stepsPerFrame = std::max(stepsPerFrame / 2, 1);
    }


    private:
    std::vector<SortScene*> scenes;
    int currentIndex = 0;
    int stepsPerFrame = 1;

    void DrawHUD(int screenW)
    {
        DrawRectangle(0, 0, screenW, 52, { 12, 12, 20, 240 });
        DrawLine(0, 52, screenW, 52, { 60, 60, 80, 180 });

        if (scenes.empty())
            return;

        SortScene* current = scenes[currentIndex];
        const char* title = current->GetName().c_str();
        DrawText(title, 16, 14, 24, WHITE);

        int dotX = screenW / 2 - (int)scenes.size() * 18 / 2;
        for (int k = 0; k < (int)scenes.size(); k++)
        {
            Color dotCol = (k == currentIndex) ? WHITE : Color{ 80, 80, 100, 255 };
            DrawCircle(dotX + k * 20, 26, 5, dotCol);
        }

        const char* hint = "[ENTER] Next [R] Reset [UP/DN] Speed";
        int hintW = MeasureText(hint, 14);
        DrawText(hint, screenW - hintW - 16, 18, 14, { 130, 130, 150, 255 });

        std::string speed = "Speed: " + std::to_string(stepsPerFrame) + "x";
        DrawText(speed.c_str(), 16, 38, 12, { 100, 100, 130, 255 });


        if (current->IsSorted())
        {
            const char* done = "SORTED";
            int tworp = MeasureText(done, 16);
            DrawRectangle(screenW / 2 - tworp / 2 - 10, 14, tworp + 20, 24, BarArray::COL_SORTED);
            DrawText(done, screenW / 2 - tworp / 2, 18, 16, BLACK);
        }
    }
};
