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
    Texture2D nebula {LoadTexture("textures/12_nebula_spritesheet.png")};
    Rectangle nebulaRec
    {
        0.0,
        0.0,
        nebula.width/8,
        nebula.height/8
    };
    Vector2 nebulaPos {windowDimensions[0], windowDimensions[1] - nebulaRec.height};
    int nebFram{0};
    const float nebUpdateTimer{1.0/12.0};
    float nebRunningTime{0};
    
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

        // update nebula texture position
        nebulaPos.x += nebulaVelocity * deltaTime;

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

        // update nebula
        nebRunningTime += deltaTime;
        if (nebRunningTime >= nebUpdateTimer)
        {
            nebRunningTime = 0.0;
            nebulaRec.x = nebFram * nebulaRec.width;
            nebFram++;
            if (nebFram > 7)
            {
                nebFram = 0;
            }
        }
        
        
        // draw nebula
        DrawTextureRec(nebula, nebulaRec, nebulaPos, WHITE);
        
        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rect, scarfyData.pos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}