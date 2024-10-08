/********************************************************************************************************************************************************************************************
*
*   Raylib A.P.I - Skybox loading and drawing
*   A.P.I Created by Zach Noland (@MuzakyGood)
*
*   License in origin code: 
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*   
*   Copyright (c) 2017-2023 Ramon Santamaria (@raysan5)
*
*********************************************************************************************************************************************************************************************/

#ifndef SKYBOX_H
#define SKYBOX_H

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"      // Required for: MatrixPerspective(), MatrixLookAt()

#ifdef __cplusplus
extern "C" {
#endif

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

typedef struct {
bool useHDR; 
char skyboxFileName[256]; 
Shader shaderbox;
Model modelbox;
Mesh meshbox;
} Skyboxlib;

extern Skyboxlib skybox;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Generate cubemap (6 faces) from equirectangular (panorama) texture
static TextureCubemap GenTextureCubemap(Shader shader, Texture2D panorama, int size, int format);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*  Skybox declaration, put this inside InitWindow(), put this function inside typedef struct Skyboxlib variable.
    INCLUDE: path image(png), path texture(hdr), path shaders(vs,fs), path cubemap(vs,fs).
 */
Skyboxlib SkyboxLoad(const char* ImgSkyboxPath, const char* TextureHDRPath, const char* SkyboxVSPath, const char* SkyboxFSPath, const char* CubemapVSPath, const char* CubemapFSPath) {
    
    Skyboxlib skybox = { false, "", {0}, {0}, {0} };
    
    // Load skybox model
    skybox.meshbox = GenMeshCube(1.0f, 1.0f, 1.0f);
    skybox.modelbox = LoadModelFromMesh(skybox.meshbox);

    // Load skybox shader and set required locations
    skybox.modelbox.materials[0].shader = LoadShader(TextFormat(SkyboxVSPath, GLSL_VERSION), TextFormat(SkyboxFSPath, GLSL_VERSION));

    skybox.shaderbox = LoadShader(TextFormat(CubemapVSPath, GLSL_VERSION), TextFormat(CubemapFSPath, GLSL_VERSION));

    int environmentMapValue[1] = { MATERIAL_MAP_CUBEMAP };
    SetShaderValue(skybox.modelbox.materials[0].shader, GetShaderLocation(skybox.modelbox.materials[0].shader, "environmentMap"), environmentMapValue, SHADER_UNIFORM_INT);

    int doGammaValue[1] = { skybox.useHDR ? 1 : 0 };
    SetShaderValue(skybox.modelbox.materials[0].shader, GetShaderLocation(skybox.modelbox.materials[0].shader, "doGamma"), doGammaValue, SHADER_UNIFORM_INT);

    int vflippedValue[1] = { skybox.useHDR ? 1 : 0 };
    SetShaderValue(skybox.modelbox.materials[0].shader, GetShaderLocation(skybox.modelbox.materials[0].shader, "vflipped"), vflippedValue, SHADER_UNIFORM_INT);

    int equirectangularMapValue[1] = { 0 };
    SetShaderValue(skybox.shaderbox, GetShaderLocation(skybox.shaderbox, "equirectangularMap"), equirectangularMapValue, SHADER_UNIFORM_INT);

    if (skybox.useHDR) {
        TextCopy(skybox.skyboxFileName, TextureHDRPath);
        Texture2D panorama = LoadTexture(skybox.skyboxFileName);
        skybox.modelbox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = GenTextureCubemap(skybox.shaderbox, panorama, 1024, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
        UnloadTexture(panorama);
    } else {
        Image img = LoadImage(ImgSkyboxPath);
        skybox.modelbox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = LoadTextureCubemap(img, CUBEMAP_LAYOUT_AUTO_DETECT);
        UnloadImage(img);
    }

    return skybox;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Skybox need update, put this function in main loop (while), especialy update.
void SkyboxUpdate(Skyboxlib* skybox) {
    if (IsFileDropped()) {
        FilePathList droppedFiles = LoadDroppedFiles();
        if (droppedFiles.count == 1) {
            if (IsFileExtension(droppedFiles.paths[0], ".png;.jpg;.hdr;.bmp;.tga")) {
                UnloadTexture(skybox->modelbox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture);

                if (skybox->useHDR) {
                    Texture2D panorama = LoadTexture(droppedFiles.paths[0]);
                    skybox->modelbox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = GenTextureCubemap(skybox->shaderbox, panorama, 1024, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
                    UnloadTexture(panorama);
                } else {
                    Image img = LoadImage(droppedFiles.paths[0]);
                    skybox->modelbox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = LoadTextureCubemap(img, CUBEMAP_LAYOUT_AUTO_DETECT);
                    UnloadImage(img);
                }

                TextCopy(skybox->skyboxFileName, droppedFiles.paths[0]);
            }
        }
        UnloadDroppedFiles(droppedFiles);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Skybox need drawmodel, put this function in BeginDrawing() inside Begin3DMode(camera).
void DrawSkyboxModel(Skyboxlib* skybox) {
    rlDisableBackfaceCulling();
    rlDisableDepthMask();
    DrawModel(skybox->modelbox, (Vector3){0, 0, 0}, 1.0f, WHITE);
    rlEnableBackfaceCulling();
    rlEnableDepthMask();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Skybox need drawtexture, put this function in BeginDrawing() below End3DMode().
void DrawSkyboxTexture(Skyboxlib* skybox) {
    if (skybox->useHDR) DrawText(TextFormat("Panorama image from hdrihaven.com: %s", GetFileName(skybox->skyboxFileName)), 10, GetScreenHeight() - 20, 10, BLACK);
    else DrawText(TextFormat(": %s", GetFileName(skybox->skyboxFileName)), 10, GetScreenHeight() - 20, 10, BLACK);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Skybox need Unload, put this function in de-initialization. 
void UnloadSkybox(Skyboxlib* skybox) {
    UnloadShader(skybox->modelbox.materials[0].shader);
    UnloadTexture(skybox->modelbox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture);
    UnloadModel(skybox->modelbox);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static TextureCubemap GenTextureCubemap(Shader shader, Texture2D panorama, int size, int format)
{
    TextureCubemap cubemap = { 0 };

    rlDisableBackfaceCulling();     // Disable backface culling to render inside the cube

    // STEP 1: Setup framebuffer
    //------------------------------------------------------------------------------------------
    unsigned int rbo = rlLoadTextureDepth(size, size, true);
    cubemap.id = rlLoadTextureCubemap(0, size, format);

    unsigned int fbo = rlLoadFramebuffer(size, size);
    rlFramebufferAttach(fbo, rbo, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_RENDERBUFFER, 0);
    rlFramebufferAttach(fbo, cubemap.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_CUBEMAP_POSITIVE_X, 0);

    // Check if framebuffer is complete with attachments (valid)
    if (rlFramebufferComplete(fbo)) TraceLog(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully", fbo);
    //------------------------------------------------------------------------------------------

    // STEP 2: Draw to framebuffer
    //------------------------------------------------------------------------------------------
    // NOTE: Shader is used to convert HDR equirectangular environment map to cubemap equivalent (6 faces)
    rlEnableShader(shader.id);

    // Define projection matrix and send it to shader
    Matrix matFboProjection = MatrixPerspective(90.0*DEG2RAD, 1.0, RL_CULL_DISTANCE_NEAR, RL_CULL_DISTANCE_FAR);
    rlSetUniformMatrix(shader.locs[SHADER_LOC_MATRIX_PROJECTION], matFboProjection);

    // Define view matrix for every side of the cubemap
    Matrix fboViews[6] = {
        MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  1.0f,  0.0f,  0.0f }, (Vector3){ 0.0f, -1.0f,  0.0f }),
        MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){ -1.0f,  0.0f,  0.0f }, (Vector3){ 0.0f, -1.0f,  0.0f }),
        MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f,  1.0f,  0.0f }, (Vector3){ 0.0f,  0.0f,  1.0f }),
        MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f, -1.0f,  0.0f }, (Vector3){ 0.0f,  0.0f, -1.0f }),
        MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f,  0.0f,  1.0f }, (Vector3){ 0.0f, -1.0f,  0.0f }),
        MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f,  0.0f, -1.0f }, (Vector3){ 0.0f, -1.0f,  0.0f })
    };

    rlViewport(0, 0, size, size);   // Set viewport to current fbo dimensions
    
    // Activate and enable texture for drawing to cubemap faces
    rlActiveTextureSlot(0);
    rlEnableTexture(panorama.id);

    for (int i = 0; i < 6; i++)
    {
        // Set the view matrix for the current cube face
        rlSetUniformMatrix(shader.locs[SHADER_LOC_MATRIX_VIEW], fboViews[i]);
        
        // Select the current cubemap face attachment for the fbo
        // WARNING: This function by default enables->attach->disables fbo!!!
        rlFramebufferAttach(fbo, cubemap.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_CUBEMAP_POSITIVE_X + i, 0);
        rlEnableFramebuffer(fbo);

        // Load and draw a cube, it uses the current enabled texture
        rlClearScreenBuffers();
        rlLoadDrawCube();

        // ALTERNATIVE: Try to use internal batch system to draw the cube instead of rlLoadDrawCube
        // for some reason this method does not work, maybe due to cube triangles definition? normals pointing out?
        // TODO: Investigate this issue...
        //rlSetTexture(panorama.id); // WARNING: It must be called after enabling current framebuffer if using internal batch system!
        //rlClearScreenBuffers();
        //DrawCubeV(Vector3Zero(), Vector3One(), WHITE);
        //rlDrawRenderBatchActive();
    }
    //------------------------------------------------------------------------------------------

    // STEP 3: Unload framebuffer and reset state
    //------------------------------------------------------------------------------------------
    rlDisableShader();          // Unbind shader
    rlDisableTexture();         // Unbind texture
    rlDisableFramebuffer();     // Unbind framebuffer
    rlUnloadFramebuffer(fbo);   // Unload framebuffer (and automatically attached depth texture/renderbuffer)

    // Reset viewport dimensions to default
    rlViewport(0, 0, rlGetFramebufferWidth(), rlGetFramebufferHeight());
    rlEnableBackfaceCulling();
    //------------------------------------------------------------------------------------------

    cubemap.width = size;
    cubemap.height = size;
    cubemap.mipmaps = 1;
    cubemap.format = format;

    return cubemap;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif