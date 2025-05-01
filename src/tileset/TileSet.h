#pragma once
#include <string>
#include <raylib.h>
#include <vector>

#include "TileSetCell.h"
#include "TileSetGui.h"
#include "TileSetTexture.h"
#include "src/Constants.h"

class TileSet {
    TileSetGui *gui;

    std::vector<TileSetTexture> tileSetList;
    int selectedTileSetIndex = -1;

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

    void addTileSet(const std::string &texturePath);

    void deleteTileSet(int index);

    void draw() const;

    void toggleGrid() {
        isGridEnabled = !isGridEnabled;
    }
};
