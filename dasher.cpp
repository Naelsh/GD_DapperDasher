#include "raylib.h"

int main()
{
    const int windowWidth {512};
    const int windowHeight {380};
    InitWindow(windowWidth,windowHeight,"Dapper dasher");

    // tecture for character setup
    Texture2D scarfy {LoadTexture("textures/scarfy.png")};
    Rectangle scarfyRec;
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0;
    scarfyRec.y = 0;
    Vector2 scarfyPos;
    scarfyPos.x = windowWidth/2 - scarfyRec.width/2;
    scarfyPos.y = windowHeight - scarfyRec.height;

    int velocity {0};
    const int jumpVelocity {-22};
    bool isInAir {!(scarfyPos.y >= windowHeight - scarfyRec.height)};

    // accelaration pixels/frame
    const int gravity {1};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        // game logic
        
        // ground check
        if (scarfyPos.y >= windowHeight - scarfyRec.height)
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
        
        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity;
        }

        // update texture

        scarfyPos.y += velocity;
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}