# **SkyboxLib**
<p><b>"CREATE A SKYBOX IN RAYLIB EASILY"</b></p>
<a href="https://www.raylib.com" target="_blank" rel="noreferree">
<img src="https://upload.wikimedia.org/wikipedia/commons/f/f4/Raylib_logo.png" alt="raylib" width="45" height="50"> <img src="https://upload.wikimedia.org/wikipedia/commons/1/19/C_Logo.png" alt="C" width="45" height="50"> <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/18/ISO_C%2B%2B_Logo.svg/1200px-ISO_C%2B%2B_Logo.svg.png" alt="C++" width="45" height="50"></a>

# **📰API Description📰**
<p>SkyboxLib is an API used in the <b>Raylib</b> Library. This API was created to make it easier to create a skybox on 3D graphics in Raylib.The code examples are based on the basic structure of raylib and are easy to use for beginners.
This header works for <b>C/C++</b> .The code examples that I provide use Visual Studio Code and the Json Linker. Press <mark>F5</mark> for debbugging if using the json file that my code provided.<br>
NOTE: Make sure to format the texture/image <mark>.png</mark> and the image size is <mark>2048 x 1536</mark> <br>
(For now this API cannot set the image size costomically)</p>

<img src="Example/Result_Skybox.png" alt="SkyboxLib Example" width="496" height="264">

# **💾Cheatsheet💾**

```c
Skyboxlib SkyboxLoad(const char* ImgSkyboxPath, const char* TextureHDRPath, const char* SkyboxVSPath, const char* SkyboxFSPath, const char* CubemapVSPath, const char* CubemapFSPath);
void SkyboxUpdate(Skylib* skybox);
void DrawSkyboxModel(Skylib* skybox);
void DrawSkyboxTexture(Skylib* skybox);
void UnloadSkybox(Skylib* skybox);
```

# **📂Structure Project Example📁**

```bash
MyProject
    │   main.c
    │   main.code-workspace
    │   Makefile
    │   Makefile.Android
    │   skybox.h
    ├───.vscode
    │       c_cpp_properties.json
    │       launch.json
    │       settings.json
    │       tasks.json
    ├───image
    │   │   skyboxsea1.png
    │   │
    │   └───skybox
    │           dresden_square_1k.hdr
    │           dresden_square_2k.hdr
    └───shader
        ├───glsl100
        │       cubemap.fs
        │       cubemap.vs
        │       skybox.fs
        │       skybox.vs
        └───glsl330
                cubemap.fs
                cubemap.vs
                skybox.fs
                skybox.vs
```

# **💿Setup SkyLib API💿**
<p><b>TOOL/LIBRARY:</b></p>
            1. Visual Studio Code (It's up to you what text editor you use)
            <br>
            2. Linker Library (CMake, JSON, Lua Scripting, etc)
            <br>
            3. Raylib Installer (W64DevKit)
            <br>
            4. Image/Texture Skybox
            <br>
            5. skybox.h

# **📋Example C/C++ Code📋**
<p>1. Example Code C :</p>

```c
#include <stdio.h>
#include "raylib.h"
#include "skybox.h"

int main(void) {
    InitWindow(800, 600, "Skybox Example");

    // Load assets skybox (Make sure the path of the image is correct).
    Skyboxlib skynoon = SkyboxLoad("resources/skybox.png", NULL, // Add an HDR Path texture if you want, otherwise just write NULL
                                  "resources/skybox.vs", "resources/skybox.fs", 
                                  "resources/cubemap.vs", "resources/cubemap.fs");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; 
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE;

    while (!WindowShouldClose()) {

        UpdateCamera(&camera, CAMERA_FREE); 

        SkyboxUpdate(&skynoon); // Update skybox.

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
            DrawSkyboxModel(&skynoon);    // Draw the skybox model.

            DrawGrid(10, 1.0f);

        EndMode3D();
            // DrawSkyboxTexture(&skynoon);    // Draw the skybox texture (If you use HDR texture).
        EndDrawing();
    }

    UnloadSkybox(&skynoon);    // Clean skybox resources
    CloseWindow();
    return 0;
}
```

<p>2. Example Code C++ :</p>

```cpp
#include <iostream>
#include "raylib.h"
#include "skybox.h"

int main(void) {
    InitWindow(800, 600, "Skybox Example");
    
    // Load assets skybox (Make sure the path of the image is correct).
    Skyboxlib skynoon = SkyboxLoad("resources/skybox.png", NULL, // Add an HDR Path texture if you want, otherwise just write NULL
                                  "resources/skybox.vs", "resources/skybox.fs", 
                                  "resources/cubemap.vs", "resources/cubemap.fs");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; 
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          
    camera.fovy = 45.0f;                                
    camera.projection = CAMERA_PERSPECTIVE;

    while (!WindowShouldClose()) {

        UpdateCamera(&camera, CAMERA_FREE); 
        
        SkyboxUpdate(&skynoon); // Update skybox.

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        BeginMode3D(camera);
            DrawSkyboxModel(&skynoon);    // Draw the skybox model.

            DrawGrid(10, 1.0f);
            
        EndMode3D();
            // DrawSkyboxTexture(&skynoon);    // Draw the skybox texture (If you use HDR texture).
        EndDrawing();
    }

    UnloadSkybox(&skynoon);    // Clean skybox resources
    CloseWindow();
    return 0;
}
```

# **🔨Setup API**
1. First you must have Raylib or have Raylib installed.
2. Clone repository from github SkyboxLib.
3. Copy the skybox.h Header to your project
4. If you are using a private linker (like Cmake), make sure you have added skybox.h .
5. Run MakeFile (If u use VSCode u must press F5)

```bash
$ git clone https://github.com/MuzakyGood/SkyboxLib
$ cp SkyboxLib/skybox.h <your_project>
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