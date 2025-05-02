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

    auto menuBar = new MenuBar(
        [](const int newValue) {
            std::cout << "Map width: " << newValue << std::endl;
        },
        [](const int newValue) {
            std::cout << "Map height: " << newValue << std::endl;
        }
    );

    const auto tileset = new TileSet();
    // tileset->loadTexture("assets/AutotileExample.png");

    while (!WindowShouldClose()) {
        // update
        tileset->update();

        BeginDrawing();
        ClearBackground(Color{68, 71, 90});
        rlImGuiBegin();

        ImGui::PushStyleColor(ImGuiCol_WindowBg, MENU_BAR_COLOR);
        ImGui::PushStyleColor(ImGuiCol_Button, BUTTON_COLOR);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, BUTTON_HOVERED_COLOR);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, BUTTON_ACTIVE_COLOR);

        ImGui::PushStyleColor(ImGuiCol_CheckMark, SELECTION_COLOR);

        ImGui::PushStyleColor(ImGuiCol_MenuBarBg, MENU_BAR_COLOR);
        ImGui::PushStyleColor(ImGuiCol_PopupBg, MENU_BAR_COLOR);
        ImGui::PushStyleColor(ImGuiCol_Border, MENU_BAR_COLOR);
        ImGui::PushStyleColor(ImGuiCol_Header, BUTTON_COLOR);
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, BUTTON_HOVERED_COLOR);
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, BUTTON_ACTIVE_COLOR);

        ImGui::PushStyleColor(ImGuiCol_Tab, BUTTON_ACTIVE_COLOR);
        ImGui::PushStyleColor(ImGuiCol_TabHovered, BUTTON_HOVERED_COLOR);
        ImGui::PushStyleColor(ImGuiCol_TabActive, SELECTION_COLOR);

        ImGui::PushStyleColor(ImGuiCol_FrameBg, FRAME_BACKGROUND_COLOR);
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, FRAME_BACKGROUND_HOVERED_COLOR);
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, FRAME_BACKGROUND_ACTIVE_COLOR);
        ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, SELECTION_COLOR);

        ImGui::PushStyleColor(ImGuiCol_TitleBg, MENU_BAR_COLOR);
        ImGui::PushStyleColor(ImGuiCol_TitleBgActive, SELECTION_COLOR);
        ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, BUTTON_COLOR);

        // draw
        tileset->draw();
        menuBar->draw();

        ImGui::PopStyleColor(21);

        rlImGuiEnd();
        DrawFPS(GetScreenWidth() - 100, 10);
        EndDrawing();
    }

    delete tileset;

    return 0;
}
