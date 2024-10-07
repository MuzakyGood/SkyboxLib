# ***🏕️⛰️⛅SkyboxLib API⛅⛰️🏕️***
<p>CREATE A SKYBOX IN RAYLIB EASILY</p>

# **📰API Description📰**
<p>SkyboxLib is an API used in the <b>Raylib</b> Library. This API was created to make it easier to create a skybox on 3D graphics in Raylib.The code examples are based on the basic structure of raylib and are easy to use for beginners.
This header works for <b>C/C++</b> . Press <mark>F5</mark> for debbugging if using the json file that my code provided.<br>
NOTE: Make sure to format the texture/image <mark>.png</mark> and the image size is <mark>2048 x 1536</mark> <br>
(For now this API cannot set the image size costomically)</p>

<img src="Example/Result_Skybox.png" alt="SkyboxLib Example" width="496" height="264">

# **💾Cheatsheet💾**

```c
Skyboxlib SkyboxLoad(const char* ImgSkyboxPath, const char* TextureHDRPath, const char* SkyboxVSPath, const char* SkyboxFSPath, const char* CubemapVSPath, const char* CubemapFSPath);
void SkyboxUpdate(Skylib* skybox);
void DrawSkybox(Skylib* skybo);
void DrawSkyboxTexture(Skylib* skybox);
void UnloadSkybox(Skylib* skybox);
```

# **💿Setup SkyLib API💿**
<p><b>TOOL/LIBRARY:</b></p>
            1. Visual Studio Code (It's up to you what text editor you use)
            <br>
            2. Linker Library (CMake, JSON, Lua Scripting)
            <br>
            3. Raylib Installer (W64DevKit)
            <br>
            4. Image/Texture Skybox

# **📋Example C/C++ Code📋**
<p>1. Example Code C :</p>

```c
#include <stdio.h>
#include "raylib.h"
#include "skybox.h"

int main(void) {
    InitWindow(800, 600, "Skybox Example");

    // Load assets skybox (Make sure the path of the image is correct).
    Skyboxlib skybox = SkyboxLoad("resources/skybox.png", NULL, // Add an HDR Path texture if you want, otherwise just write NULL
                                  "resources/skybox.vs", "resources/skybox.fs", 
                                  "resources/cubemap.vs", "resources/cubemap.fs");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; 
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
            DrawSkybox(&skybox);    // Draw the skybox model.
        EndMode3D();
            // DrawSkyboxTexture(&skynoon);    // Draw the skybox texture (If you use HDR texture).
        EndDrawing();
    }

    UnloadSkybox(&skybox);    // Clean skybox resources
    CloseWindow();
    return 0;
}
```

<p>2. Example Code C++ :</p>

```cpp
#include <iostream>
#include "raylib.h"
#include "skybox.h"

int main() {
    InitWindow(800, 600, "Skybox Example");
    
    // Load assets skybox (Make sure the path of the image is correct).
    Skyboxlib skybox = SkyboxLoad("resources/skybox.png", NULL, // Add an HDR Path texture if you want, otherwise just write NULL
                                  "resources/skybox.vs", "resources/skybox.fs", 
                                  "resources/cubemap.vs", "resources/cubemap.fs");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; 
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        BeginMode3D(camera);
            DrawSkybox(&skybox);    // Draw the skybox model.
        EndMode3D();
            // DrawSkyboxTexture(&skynoon);    // Draw the skybox texture (If you use HDR texture).
        EndDrawing();
    }

    UnloadSkybox(&skybox);    // Clean skybox resources
    CloseWindow();
    return 0;
}
```

# **Important**
- I used the code example on the Raylib website and bit edit. <br> 
- I added a function and a typedef struct,and edited for variable pointers to support A.P.I to make it easier for beginners to use. <br>
- Code originally created by Ramon Santamaria (@raysan5) <br>
- It is allowed to use the code very freely: modify, distribute, and use it for personal or commercial purposes, <br>
but must still include the original credit and header creator if it is to be edited and published.

# **LICENCE**
BSD 2-Clause License

Copyright (c) 2024, Zach Noland

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# **😄Good luck trying SkyboxLib😄**