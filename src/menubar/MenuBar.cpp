#include "MenuBar.h"

#include "imgui.h"
#include <raylib.h>

MenuBar::MenuBar() {
}

void MenuBar::draw() const {
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(GetScreenWidth(), 0), ImGuiCond_Always);

    if (ImGui::Begin("MenuBar", nullptr,
                     ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration)) {
        drawMenuBar();
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

        if (ImGui::BeginMenu("Editar")) {
            if (ImGui::MenuItem("Copiar")) {

            }
            if (ImGui::MenuItem("Pegar")) {

            }
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
}
