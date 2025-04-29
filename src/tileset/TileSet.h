#pragma once
#include <string>
#include <raylib.h>
#include <vector>

#include "TileSetCell.h"
#include "src/Constants.h"

class TileSet {
    unsigned int AREA_HEIGHT;

    std::string path;
    Texture2D texture = {};
    Camera2D camera = {
        .offset = {TILESET_DEFAULT_X, TILESET_DEFAULT_Y},
        .zoom = 1
    };

    unsigned int tileWidth;
    unsigned int tileHeight;

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
