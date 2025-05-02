#include "TileSet.h"

#include <iostream>

#include "src/Constants.h"

TileSet::TileSet() : tileWidth(DEFAULT_TILE_WIDTH), tileHeight(DEFAULT_TILE_HEIGHT) {
    gui = new TileSetGui(tileWidth, tileHeight, tileSetList, selectedTileSetIndex,
                         [this](const std::string &path) { addTileSet(path); },
                         [this](const int index) { deleteTileSet(index); });
    selectedCells = std::vector<TileSetCell>();
    mousePosition = GetMousePosition();
    worldPositionTileSet = GetScreenToWorld2D(mousePosition, camera);
}

TileSet::~TileSet() {
    delete gui;
    for (const auto &tileSetTexture: tileSetList) {
        UnloadTexture(tileSetTexture.texture);
    }
}

void TileSet::addTileSet(const std::string &texturePath) {
    const TileSetTexture tileSetTexture = {
        .path = texturePath,
        .texture = LoadTexture(texturePath.c_str())
    };

    tileSetList.push_back(tileSetTexture);

    if (selectedTileSetIndex == -1 || tileSetList.size() == 1) {
        selectedTileSetIndex = tileSetList.size() - 1;
    }
}

void TileSet::deleteTileSet(int index) {
    if (index < 0 || index >= tileSetList.size()) return;

    UnloadTexture(tileSetList[index].texture);

    tileSetList.erase(tileSetList.begin() + index);

    if (tileSetList.empty()) {
        selectedTileSetIndex = -1;
    } else if (selectedTileSetIndex >= tileSetList.size()) {
        selectedTileSetIndex = tileSetList.size() - 1;
    }
}

void TileSet::update() {
    if (tileSetList.empty() || selectedTileSetIndex == -1) return;

    const float deltaTime = GetFrameTime();

    camera.zoom = tileSetList[selectedTileSetIndex].cameraZoom;
    camera.target = tileSetList[selectedTileSetIndex].cameraTarget;

    mousePosition = GetMousePosition();
    worldPositionTileSet = GetScreenToWorld2D(mousePosition, camera);

    if (isMouseInsideTileSetZone()) {
        zoomCamera(deltaTime);

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) || IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
            moveCamera();
        }
    }

    tileSetList[selectedTileSetIndex].cameraZoom = camera.zoom;
    tileSetList[selectedTileSetIndex].cameraTarget = camera.target;
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

    EndScissorMode();
}

void TileSet::drawGrid() const {
    if (tileWidth == 0 || tileHeight == 0) return;

    for (unsigned int vertical = 0; vertical <= tileSetList[selectedTileSetIndex].texture.width;
         vertical += tileWidth) {
        DrawLine(vertical, 0, vertical, tileSetList[selectedTileSetIndex].texture.height, gridColor);
    }

    for (unsigned int horizontal = 0; horizontal <= tileSetList[selectedTileSetIndex].texture.height;
         horizontal += tileHeight) {
        DrawLine(0, horizontal, tileSetList[selectedTileSetIndex].texture.width, horizontal, gridColor);
    }
}

bool TileSet::isMouseInsideTileSetZone() const {
    return mousePosition.x > 0 && mousePosition.x < static_cast<float>(TILESET_AREA_WIDTH) &&
           mousePosition.y > TILESET_AREA_VERTICAL_POSITION && mousePosition.y < GetScreenHeight() - gui->getHeight();
}

bool TileSet::isMouseInsideTileSet() const {
    return worldPositionTileSet.x > 0 && worldPositionTileSet.x < tileSetList[selectedTileSetIndex].texture.width &&
           mousePosition.x < TILESET_AREA_WIDTH &&
           worldPositionTileSet.y > 0 && worldPositionTileSet.y < tileSetList[selectedTileSetIndex].texture.height &&
           mousePosition.y < GetScreenHeight() - gui->getHeight();
}

void TileSet::zoomCamera(const float deltaTime) {
    if (GetMouseWheelMoveV().y != 0) {
        const Vector2 worldBeforeZoom = GetScreenToWorld2D(mousePosition, camera);

        camera.zoom += GetMouseWheelMoveV().y * deltaTime;

        if (camera.zoom < 0.25f) camera.zoom = 0.25f;

        const Vector2 worldAfterZoom = GetScreenToWorld2D(mousePosition, camera);

        camera.target.x += worldBeforeZoom.x - worldAfterZoom.x;
        camera.target.y += worldBeforeZoom.y - worldAfterZoom.y;
    }
}

void TileSet::moveCamera() {
    camera.target.x -= GetMouseDelta().x / camera.zoom;
    camera.target.y -= GetMouseDelta().y / camera.zoom;
}
