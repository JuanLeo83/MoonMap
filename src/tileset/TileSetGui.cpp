#include "TileSetGui.h"

#include "imgui.h"
#include "ImGuiFileDialog.h"
#include "rlImGui.h"
#include "src/Constants.h"

TileSetGui::TileSetGui(int &tileWidth, int &tileHeight, bool &showGrid,
                       std::vector<TileSetTexture> &tileSetList, int &selectedTileSetIndex,
                       std::function<void(const std::string &)> onAddTileSet,
                       std::function<void(int)> onDeleteTileSet) : tileWidth(tileWidth),
                                                                   tileHeight(tileHeight),
                                                                   showGrid(showGrid),
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

        ImGui::AlignTextToFramePadding();
        ImGui::Text("Tile width:");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(40);
        ImGui::DragInt("##TileWidth", &tileWidth, 1.0f, 0, INT_MAX);

        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();
        ImGui::Spacing();
        ImGui::SameLine();

        ImGui::AlignTextToFramePadding();
        ImGui::Text("Tile height:");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(40);
        ImGui::DragInt("##TileHeight", &tileHeight, 1.0f, 0, INT_MAX);

        if (!tileSetList.empty() && selectedTileSetIndex >= 0) {
            ImGui::Checkbox("Show grid", &showGrid);
        }

        if (!tileSetList.empty() && selectedTileSetIndex >= 0) {
            ImGui::SameLine();
            ImGui::Checkbox("Autotile", &tileSetList[selectedTileSetIndex].isAutoTiling);
        }
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

float TileSetGui::getHeight() {
    return MENU_BAR_HEIGHT * 2.1f;
}
