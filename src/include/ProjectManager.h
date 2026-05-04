#pragma once
#include "StateMachine.h"
#include "MenuManager.h"
#include "SceneManager.h"
#include "MazeManager.h"
#include "BubbleSortScene.h"
#include "InsertionSortScene.h"
#include "HeapSortScene.h"
#include "BFSPath.h"
#include "DFSPath.h"
#include "AStarPath.h"
#include "BarArray.h"
#include "raylib.h"


class ProjectManager
{
    public:
    ProjectManager(int barCount = 80) : state(StateMachine::Menu) 
    {
        sortingManager.AddScene(new BubbleSortScene(barCount));
        sortingManager.AddScene(new InsertionSortScene(barCount));
        sortingManager.AddScene(new HeapSortScene(barCount));

        mazeManager.AddScene(new BFSPath());
        mazeManager.AddScene(new DFSPath());
        mazeManager.AddScene(new AStarPath());
    }


    void HandleInput() 
    {
        switch (state) 
        {
            case StateMachine::Menu: 
            {
                StateMachine next = menu.HandleInput();
                if (next != StateMachine::Menu) state = next;
                break;
            }

            case StateMachine::Sorting: 
            {
                if (IsKeyPressed(KEY_ESCAPE)) { state = StateMachine::Menu; break; }
                if (IsKeyPressed(KEY_ENTER)) sortingManager.NextScene();
                if (IsKeyPressed(KEY_R)) sortingManager.ResetCurrent();
                if (IsKeyPressed(KEY_UP)) sortingManager.IncreaseSpeed();
                if (IsKeyPressed(KEY_DOWN)) sortingManager.DecreaseSpeed();
                break;
            }

            case StateMachine::Maze: 
            {
                if (IsKeyPressed(KEY_ESCAPE)) { state = StateMachine::Menu; break; }
                if (IsKeyPressed(KEY_ENTER)) mazeManager.NextScene();
                if (IsKeyPressed(KEY_R)) mazeManager.ResetCurrent();
                if (IsKeyPressed(KEY_UP)) mazeManager.IncreaseSpeed();
                if (IsKeyPressed(KEY_DOWN)) mazeManager.DecreaseSpeed();
                break;
            }
        }
    }


    void Update() 
    {
        float dt = GetFrameTime();
        switch (state) 
        {
            case StateMachine::Menu: 
            break;

            case StateMachine::Sorting: 
            {
                for (int s = 0; s < sortingManager.GetStepsPerFrame(); ++s) 
                    sortingManager.Update();
                break;
            }

            case StateMachine::Maze:
                mazeManager.Update(dt);
                break;
        }
    }


    void Draw(int screenW, int screenH) 
    {
        switch (state) 
        {
            case StateMachine::Menu:
                ClearBackground(BarArray::COL_BG);
                menu.Draw(screenW, screenH);
                break;

            case StateMachine::Sorting:
                ClearBackground(BarArray::COL_BG);
                sortingManager.Draw(screenW, screenH);
                break;

            case StateMachine::Maze:
                ClearBackground(BarArray::COL_BG);
                mazeManager.Draw(screenW, screenH);
                break;
        }
    }


    ~ProjectManager()
    {
        UnloadFont(font);
    }


    private:
    Font font;
    StateMachine state;
    MenuScene menu;
    SceneManager sortingManager;
    MazeManager mazeManager;
};
