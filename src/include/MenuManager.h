#pragma once
#include "StateMachine.h"
#include "raylib.h"
#include <string>
#include <vector>


class MenuScene {
public:
    MenuScene() {}

    StateMachine HandleInput() 
    {
	if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
	    selectedIndex = (selectedIndex - 1 + (int)items.size()) % (int)items.size();

        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
	    selectedIndex = (selectedIndex + 1) % (int)items.size();

        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) 
        {
	    if (selectedIndex == 0)
		return StateMachine::Sorting;

            if (selectedIndex == 1)
		return StateMachine::Maze;
        }

        return StateMachine::Menu;
    }


    void Draw(int screenW, int screenH) 
    {
        const char* title = "The Awesome Algorithm Assignment";
        int textWidth = MeasureText(title, 42);
        DrawText(title, screenW / 2 - textWidth / 2, screenH / 4, 42, WHITE);

        const char* sub = "Choose your adventure:";
        int subtWidth = MeasureText(sub, 20);
        DrawText(sub, screenW / 2 - subtWidth / 2, screenH / 4 + 56, 20, { 140,140,160,255 });

        int startY = screenH / 2 - 20;

        for (int i = 0; i < (int)items.size(); i++) 
        {
            bool sel = (i == selectedIndex);

            int boxW = 340;
            int boxH = 60;
            int boxX = screenW / 2 - boxW/2;
            int boxY = startY + i * (boxH + 16);

            Color bgCol  = sel ? Color{ 60, 120, 200, 255 } : Color{ 30, 30, 42, 255 };
            Color borderCol = sel ? Color{ 100,160,255,255 } : Color{ 60, 60, 80, 255 };
            Color txtCol = sel ? WHITE : Color{ 160,160,180,255 };

            DrawRectangleRounded({(float)boxX,(float)boxY,(float)boxW,(float)boxH}, 0.2f, 8, bgCol);
            DrawRectangleRoundedLines({(float)boxX,(float)boxY,(float)boxW,(float)boxH}, 0.2f, 8, borderCol);

            int labelWidth = MeasureText(items[i].label.c_str(), 22);
            DrawText(items[i].label.c_str(), screenW / 2 - labelWidth / 2, boxY + boxH / 2 - 11, 22, txtCol);

            int dw = MeasureText(items[i].desc.c_str(), 13);
            DrawText(items[i].desc.c_str(), screenW / 2 - dw / 2, boxY + boxH / 2 + 14, 13, sel ? Color{ 180,210,255,255 } : Color{ 100,100,120,255 });
        }

        const char* hint = "UP/DOWN to select   ENTER to launch";
        int hw = MeasureText(hint, 15);
        DrawText(hint, screenW / 2 - hw / 2, screenH * 3 / 4 + 40, 15, { 100,100,120,255 });

        int arrowX = screenW / 2 - 340 / 2 - 30;
        int arrowY = startY + selectedIndex * 76 + 20;

        DrawTriangle(
            {(float)arrowX, (float)arrowY + 10},
            {(float)arrowX + 16, (float)arrowY},
            {(float)arrowX + 16, (float)arrowY + 20},
            { 100, 160, 255, 255 }
        );
    }

    private:
    int selectedIndex = 0;

    struct MenuItem 
    { 
        std::string label, desc; 
    };

    std::vector<MenuItem> items = 
    {
        {"Sorting Visualizer", "Bubble · Insertion · Heap sort"},
        {"Maze Visualizer", "BFS · DFS · A*"}
    };
};
