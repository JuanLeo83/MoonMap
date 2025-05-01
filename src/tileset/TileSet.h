#pragma once
#include <string>
#include <raylib.h>
#include <vector>

#include "TileSetCell.h"
#include "TileSetGui.h"
#include "src/Constants.h"

class TileSet {
    TileSetGui *gui;

    std::string path;
    Texture2D texture = {};
    Camera2D camera = {
        .offset = {TILESET_HORIZONTAL_PADDING, TILESET_AREA_VERTICAL_POSITION + TILESET_VERTICAL_PADDING},
        .zoom = 1
    };

    int tileWidth;
    int tileHeight;

    bool isGridEnabled = true;
    Color gridColor = DEFAULT_GRID_COLOR;

    std::vector<TileSetCell> selectedCells;

    void drawGrid() const;

public:
    explicit TileSet();

    ~TileSet();

    void loadTexture(const std::string &texturePath);

    void draw() const;

    void toggleGrid() {
        isGridEnabled = !isGridEnabled;
    }
};
