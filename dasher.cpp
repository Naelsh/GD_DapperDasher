#include "raylib.h"

int main()
{
    const int windowWidth {512};
    const int windowHeight {380};
    InitWindow(windowWidth,windowHeight,"Dapper dasher");

    // nebula variables
    Texture2D nebula {LoadTexture("textures/12_nebula_spritesheet.png")};
    Rectangle nebulaRec
    {
        0.0,
        0.0,
        nebula.width/8,
        nebula.height/8
    };
    Vector2 nebulaPos {windowWidth, windowHeight - nebulaRec.height};
    
    // velocity in pixels/s
    int nebulaVelocity {-600};

    // tecture for character setup
    Texture2D scarfy {LoadTexture("textures/scarfy.png")};
    Rectangle scarfyRec
    {
        0.0,
        0.0,
        scarfy.width/6,
        scarfy.height
    };
    Vector2 scarfyPos {windowWidth/2 - scarfyRec.width/2, windowHeight - scarfyRec.height};

    // animation frame
    int frame {0};
    const float updateTime{1.0 / 12.0};
    float runningTime{0};

    int velocity {0};
    const int jumpVelocity {-600};
    bool isInAir {!(scarfyPos.y >= windowHeight - scarfyRec.height)};

    // accelaration (pixels/frame/s)
    const int gravity {1'000};

    
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        const float deltaTime {GetFrameTime()};
        
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
            velocity += gravity * deltaTime;
            isInAir = true;
        }
        
        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVelocity;
        }

        // update nebula texture position
        nebulaPos.x += nebulaVelocity * deltaTime;

        // update scarface texture position
        scarfyPos.y += velocity * deltaTime;

        // update animation frame
        if (!isInAir)
        {
            runningTime += deltaTime;
            if (runningTime >= updateTime)
            {
                runningTime = 0.0;
                scarfyRec.x = frame * scarfyRec.width;
                frame++;
                if (frame > 5)
                {
                    frame = 0;
                }
            }
        }
        
        
        // draw nebula
        DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);
        
        // draw scarfy
        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}