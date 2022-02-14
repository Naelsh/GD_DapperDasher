#include "raylib.h"

int main()
{
    const int windowWidth {512};
    const int windowHeight {380};
    InitWindow(windowWidth,windowHeight,"Dapper dasher");

    //rectangle dimensions
    const int width{50};
    const int height{80};

    int posY {windowHeight - height};
    int velocity {0};
    const int jumpVelocity {-22};
    bool isInAir {!(posY >= windowHeight - height)};

    // accelaration pixels/frame
    const int gravity {1};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // game logic
        
        // ground check
        if (posY >= windowHeight - height)
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // apply gravity
            velocity += gravity;
            isInAir = true;
        }
        
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity;
        }

        posY += velocity;
        DrawRectangle(windowWidth/2, posY, width, height, BLUE);

        EndDrawing();
    }
    CloseWindow();
}