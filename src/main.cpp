/*******************************************************************************************
*
*   raylib [core] examples - Mouse wheel input
*
*   Example originally created with raylib 1.1, last time updated with raylib 1.3
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2023 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

//https://www.raylib.com/cheatsheet/cheatsheet.html
#include "raylib.h"
#include "game/game.h"
#include "util/time.h"

void mainLoop(Game& game, std::map<int, bool>& pressedKeys);

//#define PLATFORM_WE
#ifdef PLATFORM_WE
    #include "emscripten/emscripten.h"
#endif

void getFPS(long& fps, long& dt, long& lastUp);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - input mouse wheel");
    InitAudioDevice();

    Game game{ screenWidth, screenHeight };
    std::map<int, bool> pressedKeys{};


    // Main game loop
#ifdef PLATFORM_WE
    emscripten_set_main_loop([&game, &pressedKeys](){ mainLoop(game, pressedKeys); }, 0, 1);
#else
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        mainLoop(game, pressedKeys);
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void getFPS(long& fps, long& dt, long& lastUp) {
    static long lastUpdate = clck::getCurrentTime();
    static long lastUpdateNano = clck::getCurrentTimeNS();

    dt = clck::getCurrentTime() - lastUpdate;
    long dtNano = clck::getCurrentTimeNS() - lastUpdateNano;
    lastUpdate = clck::getCurrentTime();
    lastUpdateNano = clck::getCurrentTimeNS();

    fps = dtNano != 0? 1000000000 / dtNano: 0;
    lastUp = lastUpdate;
}

void mainLoop(Game& game, std::map<int, bool>& pressedKeys) {
    // Update
        //----------------------------------------------------------------------------------
        long fps, dt, lastUpdate;
        getFPS(fps, dt, lastUpdate);
        pressedKeys[-101] = IsMouseButtonDown(0);
        auto mousePos = GetMousePosition();
        game.setMouse(mousePos.x, mousePos.y);
        game.update(dt, pressedKeys);

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLUE);
            game.render();

        EndDrawing();
        //----------------------------------------------------------------------------------
}