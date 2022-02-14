#include "raylib.h"

int main()
{
    const int width {512};
    const int height {380};
    InitWindow(width,height,"Dapper dasher");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        EndDrawing();
    }
    CloseWindow();
}