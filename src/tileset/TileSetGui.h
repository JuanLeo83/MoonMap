#pragma once
#include <functional>
#include <vector>

#include "TileSetTexture.h"

class TileSetGui {
    static constexpr auto SELECT_TILESET = "ChooseFileDlgKey";

    int &tileWidth;
    int &tileHeight;
    bool &showGrid;
    std::vector<TileSetTexture> &tileSetList;
    int &selectedTileSetIndex;

    std::function<void(const std::string &)> onAddTileSet;
    std::function<void(int)> onDeleteTileSet;

    void selectTileSetDialog() const;

public:
    TileSetGui(int &tileWidth, int &tileHeight, bool &showGrid,
               std::vector<TileSetTexture> &tileSetList, int &selectedTileSetIndex,
               std::function<void(const std::string &)> onAddTileSet,
               std::function<void(int)> onDeleteTileSet);

    void draw();

    static float getHeight();
};
