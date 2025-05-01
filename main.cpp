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
    // tileset->loadTexture("assets/AutotileExample.png");

    while (!WindowShouldClose()) {
        // update

        BeginDrawing();
        ClearBackground(DARKGRAY);
        rlImGuiBegin();

        ImGui::PushStyleColor(ImGuiCol_WindowBg, MENU_BAR_COLOR);
        ImGui::PushStyleColor(ImGuiCol_Button, BUTTON_COLOR);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, BUTTON_HOVERED_COLOR);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, BUTTON_ACTIVE_COLOR);

        ImGui::PushStyleColor(ImGuiCol_MenuBarBg, MENU_BAR_COLOR);
        ImGui::PushStyleColor(ImGuiCol_PopupBg, MENU_BAR_COLOR);
        ImGui::PushStyleColor(ImGuiCol_Border, MENU_BAR_COLOR);
        ImGui::PushStyleColor(ImGuiCol_Header, BUTTON_COLOR);
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, BUTTON_HOVERED_COLOR);
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, BUTTON_ACTIVE_COLOR);

        ImGui::PushStyleColor(ImGuiCol_Tab, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_TabHovered, BUTTON_HOVERED_COLOR);
        ImGui::PushStyleColor(ImGuiCol_TabActive, BUTTON_ACTIVE_COLOR);

        // draw
        tileset->draw();

        menuBar->draw();

        ImGui::PopStyleColor(13);

        DrawFPS(GetScreenWidth() - 100, 10);
        rlImGuiEnd();
        EndDrawing();
    }

    delete tileset;

    return 0;
}
