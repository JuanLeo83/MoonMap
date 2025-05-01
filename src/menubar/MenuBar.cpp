#include "MenuBar.h"

#include "imgui.h"
#include <raylib.h>

MenuBar::MenuBar(
    std::function<void(int)> onWidthChangedCallback,
    std::function<void(int)> onHeightChangedCallback)
    : mapWidth(10),
      onMapWidthChanged(std::move(onWidthChangedCallback)),
      onMapHeightChanged(std::move(onHeightChangedCallback)) {
}

void MenuBar::draw() {
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(GetScreenWidth(), 0), ImGuiCond_Always);

    if (ImGui::Begin("MenuBar", nullptr,
                     ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration)) {
        drawMenuBar();

        drawMapWidthSlider();
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        drawMapHeightSlider();
    }
    ImGui::End();
}

void MenuBar::drawMenuBar() const {
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New map")) {
            }
            if (ImGui::MenuItem("Load map")) {
            }
            if (ImGui::MenuItem("Save map")) {
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Copy")) {
            }
            if (ImGui::MenuItem("Paste")) {
            }
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
}

void MenuBar::drawMapWidthSlider() {
    ImGui::AlignTextToFramePadding();
    ImGui::Text("Map width:");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(50.0f);
    if (ImGui::DragInt("##MapWidth", &mapWidth, 1.0f, 0, INT_MAX)) {
        if (onMapWidthChanged) {
            onMapWidthChanged(mapWidth);
        }
    }
}

void MenuBar::drawMapHeightSlider() {
    ImGui::AlignTextToFramePadding();
    ImGui::Text("Map height:");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(50.0f);
    if (ImGui::DragInt("##MapHeight", &mapHeight, 1.0f, 0, INT_MAX)) {
        if (onMapHeightChanged) {
            onMapHeightChanged(mapHeight);
        }
    }
}
