#include "raylib.h"

struct AnimData
{
    Rectangle rect;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rect.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    // update running time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0;

        // update animation fram
        data.rect.x = data.frame * data.rect.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{
    const int windowDimensions[2] {512, 380};
    InitWindow(windowDimensions[0],windowDimensions[1],"Dapper dasher");

    // nebula variables
    Texture2D nebulaTexture {LoadTexture("textures/12_nebula_spritesheet.png")};

    const int sizeOfNublae{30};
    AnimData nebulas[sizeOfNublae] {};

    for (int newNebIndex = 0; newNebIndex < sizeOfNublae; newNebIndex++)
    {
        nebulas[newNebIndex].rect = {0.0, 0.0, nebulaTexture.width/8.0f, nebulaTexture.height/8.0f};
        nebulas[newNebIndex].frame = 0;
        nebulas[newNebIndex].updateTime = 1.0/12.0;
        nebulas[newNebIndex].runningTime = 0;
        nebulas[newNebIndex].pos.y = windowDimensions[1] - nebulaTexture.height/8.0f;
        nebulas[newNebIndex].pos.x = windowDimensions[0] + 300 * newNebIndex;
    }
    
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
        if (isOnGround(scarfyData, windowDimensions[1]))
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

        for (int nebulaIndex = 0; nebulaIndex < sizeOfNublae; nebulaIndex++)
        {
            // move nebula
            nebulas[nebulaIndex].pos.x += nebulaVelocity * deltaTime;

            // update nebula
            nebulas[nebulaIndex] = updateAnimData(nebulas[nebulaIndex], deltaTime, 7);

            // draw nebula
            DrawTextureRec(nebulaTexture, nebulas[nebulaIndex].rect, nebulas[nebulaIndex].pos, WHITE);
        }

        // move scarface
        scarfyData.pos.y += velocity * deltaTime;

        // update animation frame
        if (!isInAir)
        {
            scarfyData = updateAnimData(scarfyData, deltaTime, 5);
        }
        
        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rect, scarfyData.pos, WHITE);

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebulaTexture);
    CloseWindow();
}