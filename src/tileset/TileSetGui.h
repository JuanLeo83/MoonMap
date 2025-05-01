#pragma once

class TileSetGui {
    int &tileWidth;
    int &tileHeight;

public:
    TileSetGui(int &tileWidth, int &tileHeight);

    void draw() const;
};

