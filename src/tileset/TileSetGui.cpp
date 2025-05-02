#include "TileSetGui.h"

#include <iostream>

#include "imgui.h"
#include "ImGuiFileDialog.h"
#include "rlImGui.h"
#include "src/Constants.h"

TileSetGui::TileSetGui(int &tileWidth, int &tileHeight, std::vector<TileSetTexture> &tileSetList,
                       int &selectedTileSetIndex,
                       std::function<void(const std::string &)> onAddTileSet,
                       std::function<void(int)> onDeleteTileSet) : tileWidth(tileWidth),
                                                                   tileHeight(tileHeight),
                                                                   tileSetList(tileSetList),
                                                                   selectedTileSetIndex(selectedTileSetIndex),
                                                                   onAddTileSet(std::move(onAddTileSet)),
                                                                   onDeleteTileSet(std::move(onDeleteTileSet)) {
}

void TileSetGui::draw() {
    ImGui::SetNextWindowPos(ImVec2(0, GetScreenHeight() - getHeight()), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(TILESET_AREA_WIDTH, getHeight()), ImGuiCond_Always);

    if (ImGui::Begin("TileSetControls", nullptr,
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration)) {
        if (ImGui::BeginTabBar("TabBar")) {
            for (int idx = 0; idx < tileSetList.size(); ++idx) {
                if (ImGui::BeginTabItem(std::to_string(idx + 1).c_str())) {
                    if (selectedTileSetIndex != idx) {
                        selectedTileSetIndex = idx;
                    }
                    ImGui::EndTabItem();
                }
            }
            ImGui::EndTabBar();
        }

        if (ImGui::Button("Add tileset")) {
            IGFD::FileDialogConfig config;
            config.flags = ImGuiFileDialogFlags_Modal;
            config.path = ".";
            ImGuiFileDialog::Instance()->OpenDialog(SELECT_TILESET, "Choose File", ".png,.jpeg,.jpg,.*", config);
        }
        ImGui::SameLine();
        ImGui::BeginDisabled(tileSetList.empty() || selectedTileSetIndex < 0);
        if (ImGui::Button("Delete tileset") && !tileSetList.empty() && selectedTileSetIndex >= 0) {
            onDeleteTileSet(selectedTileSetIndex);
        }
        ImGui::EndDisabled();

        ImGui::SetNextItemWidth(100);
        ImGui::InputInt("Tile width", &tileWidth);

        ImGui::SetNextItemWidth(100);
        ImGui::InputInt("Tile height", &tileHeight);
    }

    selectTileSetDialog();

    ImGui::End();
}

void TileSetGui::selectTileSetDialog() const {
    const auto maxSize = ImVec2(GetScreenWidth() * 0.75f, GetScreenHeight() * 0.75f);
    constexpr auto minSize = ImVec2(600, 400);
    if (ImGuiFileDialog::Instance()->Display(SELECT_TILESET, ImGuiWindowFlags_NoCollapse, minSize, maxSize)) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            onAddTileSet(ImGuiFileDialog::Instance()->GetFilePathName());
        }

        ImGuiFileDialog::Instance()->Close();
    }
}

float TileSetGui::getHeight() const {
    return MENU_BAR_HEIGHT * 2.0f;
}
