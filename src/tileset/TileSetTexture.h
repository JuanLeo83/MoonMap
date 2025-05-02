#pragma once
#include <string>
#include <raylib.h>

struct TileSetTexture {
    std::string path;
    Texture2D texture;
    float cameraZoom = 1.0f;
    Vector2 cameraTarget = {0, 0};
    bool isAutoTiling = false;
    Vector2 selectedTilePosition = {0, 0};
};
