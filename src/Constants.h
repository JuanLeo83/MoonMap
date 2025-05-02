#pragma once

#include <string>

#include "imgui.h"

const std::string EMPTY_STRING = "";

constexpr unsigned int MENU_BAR_HEIGHT = 50;
constexpr ImVec4 MENU_BAR_COLOR = {40.0f / 256, 42.0f / 256, 54.0f / 256, 1.0f};
constexpr ImVec4 BUTTON_COLOR = {189.0f / 256, 147.0f / 256, 249.0f / 256, 1.0f};
constexpr ImVec4 BUTTON_HOVERED_COLOR = {189.0f / 256, 118.0f / 256, 245.0f / 256, 1.0f};
constexpr ImVec4 BUTTON_ACTIVE_COLOR = {189.0f / 256, 168.0f / 256, 247.0f / 256, 1.0f};
constexpr ImVec4 SELECTION_COLOR = {255.0f / 256, 121.0f / 256, 198.0f / 256, 1.0f};
constexpr ImVec4 FRAME_BACKGROUND_COLOR = {0.2f, 0.2f, 0.2f, 1.0f};
constexpr ImVec4 FRAME_BACKGROUND_HOVERED_COLOR = {0.3f, 0.3f, 0.3f, 1.0f};
constexpr ImVec4 FRAME_BACKGROUND_ACTIVE_COLOR = {0.4f, 0.4f, 0.4f, 1.0f};


constexpr unsigned int TILESET_HORIZONTAL_PADDING = 10;
constexpr unsigned int TILESET_VERTICAL_PADDING = 10;
constexpr unsigned int TILESET_AREA_HORIZONTAL_POSITION = 0;
constexpr unsigned int TILESET_AREA_VERTICAL_POSITION = MENU_BAR_HEIGHT;
constexpr unsigned int TILESET_AREA_WIDTH = 300;
constexpr auto DEFAULT_GRID_COLOR = WHITE;
constexpr unsigned int DEFAULT_TILE_WIDTH = 16;
constexpr unsigned int DEFAULT_TILE_HEIGHT = 16;
constexpr Color TILESET_AREA_COLOR = {40, 42, 54, 255};
