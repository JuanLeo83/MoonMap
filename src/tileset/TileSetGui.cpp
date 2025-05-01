#include "TileSetGui.h"

#include "imgui.h"
#include "rlImGui.h"
#include "src/Constants.h"

TileSetGui::TileSetGui(int &tileWidth, int &tileHeight) : tileWidth(tileWidth), tileHeight(tileHeight) {
}

void TileSetGui::draw() const {
    ImGui::SetNextWindowPos(ImVec2(0, GetScreenHeight() - MENU_BAR_HEIGHT * 2), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(TILESET_AREA_WIDTH - 1, MENU_BAR_HEIGHT * 2), ImGuiCond_Always);

    if (ImGui::Begin("TileSetControls", nullptr,
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration)) {

        ImGui::SetNextItemWidth(100);
        ImGui::InputInt("Tile width", &tileWidth);

        ImGui::SetNextItemWidth(100);
        ImGui::InputInt("Tile height", &tileHeight);

    }
    ImGui::End();
}
