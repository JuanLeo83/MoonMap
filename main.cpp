#include <iostream>

#include <raylib.h>

#include "imgui.h"
#include "rlImGui.h"
#include "src/menubar/MenuBar.h"
#include "src/tileset/TileSet.h"

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "MoonMap");
    // SetExitKey(0);

    rlImGuiSetup(true);
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigWindowsMoveFromTitleBarOnly = true;
    io.IniFilename = nullptr;

    const MenuBar *menuBar = new MenuBar();

    const auto tileset = new TileSet();
    tileset->loadTexture("assets/AutotileExample.png");

    while (!WindowShouldClose()) {
        // update

        BeginDrawing();
        ClearBackground(DARKGRAY);

        // draw
        tileset->draw();
        menuBar->draw();

        DrawFPS(10, GetScreenHeight() - 20);

        EndDrawing();
    }

    delete tileset;

    return 0;
}
