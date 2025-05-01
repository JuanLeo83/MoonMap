#include "TileSet.h"

#include <iostream>

#include "src/Constants.h"

TileSet::TileSet() : tileWidth(DEFAULT_TILE_WIDTH), tileHeight(DEFAULT_TILE_HEIGHT) {
    gui = new TileSetGui(tileWidth, tileHeight, tileSetList, selectedTileSetIndex,
                         [this](const std::string &path) { loadTexture(path); });
    selectedCells = std::vector<TileSetCell>();
}

TileSet::~TileSet() {
    delete gui;
    for (const auto &tileSetTexture: tileSetList) {
        UnloadTexture(tileSetTexture.texture);
    }
}

void TileSet::loadTexture(const std::string &texturePath) {
    const TileSetTexture tileSetTexture = {
        .path = texturePath,
        .texture = LoadTexture(texturePath.c_str())
    };

    tileSetList.push_back(tileSetTexture);

    if (selectedTileSetIndex == -1 || tileSetList.size() == 1) {
        selectedTileSetIndex = tileSetList.size() - 1;
    }
}

void TileSet::draw() const {
    BeginScissorMode(0, 0, TILESET_AREA_WIDTH, GetScreenHeight());

    DrawRectangle(0, TILESET_AREA_VERTICAL_POSITION, TILESET_AREA_WIDTH, GetScreenHeight(), TILESET_AREA_COLOR);

    BeginMode2D(camera);

    if (!tileSetList.empty() && selectedTileSetIndex >= 0 && selectedTileSetIndex < tileSetList.size()) {
        DrawTexture(tileSetList[selectedTileSetIndex].texture, 0, 0, WHITE);
        drawGrid();
    }

    EndMode2D();

    gui->draw();

    DrawLine(TILESET_AREA_WIDTH, TILESET_AREA_VERTICAL_POSITION, TILESET_AREA_WIDTH, GetScreenHeight(), LIGHTGRAY);

    EndScissorMode();
}

void TileSet::drawGrid() const {
    if (tileWidth == 0 || tileHeight == 0) return;

    for (unsigned int vertical = 0; vertical <= tileSetList[selectedTileSetIndex].texture.width; vertical += tileWidth) {
        DrawLine(vertical, 0, vertical, tileSetList[selectedTileSetIndex].texture.height, gridColor);
    }

    for (unsigned int horizontal = 0; horizontal <= tileSetList[selectedTileSetIndex].texture.height; horizontal += tileHeight) {
        DrawLine(0, horizontal, tileSetList[selectedTileSetIndex].texture.width, horizontal, gridColor);
    }
}
