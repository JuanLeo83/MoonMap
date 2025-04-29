#include "TileSet.h"

#include "src/Constants.h"

TileSet::TileSet() : path(EMPTY_STRING), tileWidth(DEFAULT_TILE_WIDTH), tileHeight(DEFAULT_TILE_HEIGHT) {
    AREA_HEIGHT = GetScreenHeight() - SELECTED_TILES_AREA_HEIGHT;
    selectedCells = std::vector<TileSetCell>();
}

TileSet::~TileSet() {
    UnloadTexture(texture);
}

void TileSet::loadTexture(const std::string &texturePath) {
    path = texturePath;
    texture = LoadTexture(path.c_str());
}

void TileSet::draw() const {
    BeginScissorMode(0, 0, TILESET_AREA_WIDTH, AREA_HEIGHT);
    BeginMode2D(camera);

    DrawTexture(texture, 0, 0, WHITE);
    drawGrid();

    EndMode2D();
    EndScissorMode();
}

void TileSet::drawGrid() const {
    if (tileWidth == 0 || tileHeight == 0) return;

    for (unsigned int vertical = 0; vertical <= texture.width; vertical += tileWidth) {
        DrawLine(vertical, 0, vertical, texture.height, gridColor);
    }

    for (unsigned int horizontal = 0; horizontal <= texture.height; horizontal += tileHeight) {
        DrawLine(0, horizontal, texture.width, horizontal, gridColor);
    }
}
