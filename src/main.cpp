#include "raylib.h"
#include "ProjectManager.h"


static constexpr int SCREEN_W = 1400;
static constexpr int SCREEN_H = 900;
static constexpr int BAR_COUNT = 80;
static constexpr int TARGET_FPS = 60;


int main() 
{
    InitWindow(SCREEN_W, SCREEN_H, "Sara's Visualizer Project");
    SetTargetFPS(TARGET_FPS);
    SetExitKey(KEY_NULL);

    ProjectManager app(BAR_COUNT);

    while (!WindowShouldClose()) 
    {
        app.HandleInput();
        app.Update();

        BeginDrawing();

        app.Draw(SCREEN_W, SCREEN_H);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
