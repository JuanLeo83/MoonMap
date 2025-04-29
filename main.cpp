#include <iostream>

#include <raylib.h>

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "MoonMap");
    // SetExitKey(0);

    while (!WindowShouldClose()) {
        // update

        BeginDrawing();
        ClearBackground(DARKGRAY);

        // draw

        DrawFPS(10, GetScreenHeight() - 20);

        EndDrawing();
    }

    return 0;
}