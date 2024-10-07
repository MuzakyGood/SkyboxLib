/*
    Example code use API skybox.h in main.c in C

    NOTE: Follow the API structure correctly and structure it to avoid errors, 
          Skybox API functions will be marked with comments.
*/

#include <stdio.h>
#include "raylib.h"
#include "skybox.h"

int main(void) {

    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Skybox Example");

    // Load assets skybox (Make sure the path of the image is correct).
    Skyboxlib skynoon = SkyboxLoad("image/skyboxsea1.png", NULL, // Add an HDR Path texture if you want, otherwise just write NULL
                                  "shader/glsl%i/skybox.vs", "shader/glsl%i/skybox.fs", 
                                  "shader/glsl%i/cubemap.vs", "shader/glsl%i/cubemap.fs");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; 
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE;        

    Vector2 centerPosition = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
    SetMousePosition(centerPosition.x, centerPosition.y);     

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    HideCursor();
    SetTargetFPS(60);      

    while (!WindowShouldClose()) {

        UpdateCamera(&camera, CAMERA_FREE);
        if (IsKeyPressed('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        SetMousePosition(centerPosition.x, centerPosition.y);

        SkyboxUpdate(&skynoon);  // Update skybox.

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
            DrawSkyboxModel(&skynoon);    // Draw the skybox model.
            
            DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
            DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, GRAY);

            DrawGrid(10, 1.0f);

        EndMode3D();
            // DrawSkyboxTexture(&skynoon);    // Draw the skybox texture (If you use HDR texture).

            DrawRectangle( 10, 10, 320, 93, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 320, 93, BLUE);

            DrawText("Free camera default controls:", 20, 20, 10, BLACK);
            DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
            DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
            DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 10, DARKGRAY);
            DrawFPS(10, 550);

        EndDrawing();
    }

    UnloadSkybox(&skynoon);    // Clean skybox resources.
    CloseWindow();
    return 0;
}
