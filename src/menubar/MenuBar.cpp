#include "MenuBar.h"

#include "imgui.h"
#include <raylib.h>

#include "rlImGui.h"
#include "src/Constants.h"

MenuBar::MenuBar() {
}

void MenuBar::draw() const {
    rlImGuiBegin();

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(GetScreenWidth(), MENU_BAR_HEIGHT), ImGuiCond_Always);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(40.0f / 256, 42.0f / 256, 54.0f / 256, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(189.0f / 256, 147.0f / 256, 249.0f / 256, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(189.0f / 256, 118.0f / 256, 245.0f / 256, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(189.0f / 256, 168.0f / 256, 247.0f / 256, 1.0f));

    if (ImGui::Begin("TileSet Controls", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar)) {
        if (ImGui::Button("New map")) {

        }

        ImGui::SameLine();
        if (ImGui::Button("Load map")) {

        }

        ImGui::SameLine();
        if (ImGui::Button("Save map")) {

        }
    }
    ImGui::End();
    ImGui::PopStyleColor(4);

    rlImGuiEnd();

    DrawLine(0, MENU_BAR_HEIGHT + 1, GetScreenWidth(), MENU_BAR_HEIGHT + 1, LIGHTGRAY);
}
