#include "raylib.h"

struct AnimData
{
    Rectangle rect;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    const int windowDimensions[2] {512, 380};
    InitWindow(windowDimensions[0],windowDimensions[1],"Dapper dasher");

    // nebula variables
    Texture2D nebulaTexture {LoadTexture("textures/12_nebula_spritesheet.png")};

    AnimData nebulas[3] {};

    for (int newNebIndex = 0; newNebIndex < 3; newNebIndex++)
    {
        nebulas[newNebIndex].rect = {0.0, 0.0, nebulaTexture.width/8.0f, nebulaTexture.height/8.0f};
        nebulas[newNebIndex].frame = 0;
        nebulas[newNebIndex].updateTime = 1.0/12.0;
        nebulas[newNebIndex].runningTime = 0;
        nebulas[newNebIndex].pos.y = windowDimensions[1] - nebulaTexture.height/8.0f;
        nebulas[newNebIndex].pos.x = windowDimensions[0];
    }

    nebulas[0].pos.x += 0;
    nebulas[1].pos.x += 300;
    nebulas[2].pos.x += 600;
    
    // velocity in pixels/s
    int nebulaVelocity {-200};

    // Setup for scarfy
    Texture2D scarfy {LoadTexture("textures/scarfy.png")};
    AnimData scarfyData
    {
        Rectangle
        {
            0.0,
            0.0,
            scarfy.width/6,
            scarfy.height
        }

    };
    scarfyData.pos = { windowDimensions[0]/2 - scarfyData.rect.width/2, windowDimensions[1] - scarfyData.rect.height };
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0;

    int velocity {0};
    const int jumpVelocity {-600};
    bool isInAir {!(scarfyData.pos.y >= windowDimensions[1] - scarfyData.rect.height)};

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
        if (scarfyData.pos.y >= windowDimensions[1] - scarfyData.rect.height)
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

        for (int nebulaIndex = 0; nebulaIndex < 3; nebulaIndex++)
        {
            nebulas[nebulaIndex].pos.x += nebulaVelocity * deltaTime;

            // update nebula
            nebulas[nebulaIndex].runningTime += deltaTime;
            if (nebulas[nebulaIndex].runningTime >= nebulas[nebulaIndex].updateTime)
            {
                nebulas[nebulaIndex].runningTime = 0.0;
                nebulas[nebulaIndex].rect.x = nebulas[nebulaIndex].frame * nebulas[nebulaIndex].rect.width;
                nebulas[nebulaIndex].frame++;
                if (nebulas[nebulaIndex].frame > 7)
                {
                    nebulas[nebulaIndex].frame = 0;
                }
            }
            // draw nebula
            DrawTextureRec(nebulaTexture, nebulas[nebulaIndex].rect, nebulas[nebulaIndex].pos, WHITE);
        }

        // update scarface texture position
        scarfyData.pos.y += velocity * deltaTime;

        // update animation frame
        if (!isInAir)
        {
            scarfyData.runningTime += deltaTime;
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0.0;
                scarfyData.rect.x = scarfyData.frame * scarfyData.rect.width;
                scarfyData.frame++;
                if (scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }
            }
        }
        
        
        
        
        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rect, scarfyData.pos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebulaTexture);
    CloseWindow();
}