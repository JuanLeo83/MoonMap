#include "TileSet.h"

#include <iostream>
#include <raymath.h>

#include "src/Constants.h"

TileSet::TileSet() : tileWidth(DEFAULT_TILE_WIDTH), tileHeight(DEFAULT_TILE_HEIGHT) {
    gui = new TileSetGui(tileWidth, tileHeight, showGrid, tileSetList, selectedTileSetIndex,
                         [this](const std::string &path) { addTileSet(path); },
                         [this](const int index) { deleteTileSet(index); });
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

    auto &selectedTileSet = getSelectedTileSet();

    const float deltaTime = GetFrameTime();

    camera.zoom = selectedTileSet.cameraZoom;
    camera.target = selectedTileSet.cameraTarget;

    mousePosition = GetMousePosition();
    worldPositionTileSet = GetScreenToWorld2D(mousePosition, camera);

    if (isMouseInsideTileSetZone()) {
        zoomCamera(deltaTime);

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) || IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
            moveCamera();
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isMouseInsideTileSet()) {
            startDrag();
        }

        if (isDragging) {
            updateDrag();

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                endDrag();
            }
        }
    }

    selectedTileSet.cameraZoom = camera.zoom;
    selectedTileSet.cameraTarget = camera.target;
}

void TileSet::draw() const {
    BeginScissorMode(0, 0, TILESET_AREA_WIDTH, GetScreenHeight());

    DrawRectangle(0, TILESET_AREA_VERTICAL_POSITION, TILESET_AREA_WIDTH, GetScreenHeight(), TILESET_AREA_COLOR);

    BeginMode2D(camera);

    if (!tileSetList.empty() && selectedTileSetIndex >= 0 && selectedTileSetIndex < tileSetList.size()) {
        DrawTexture(getSelectedTileSet().texture, 0, 0, WHITE);
        drawGrid();
        drawSelectedTile();
    }

    EndMode2D();

    gui->draw();

    EndScissorMode();
}

void TileSet::drawGrid() const {
    if (!showGrid || tileWidth == 0 || tileHeight == 0) return;

    auto &selectedTileSet = getSelectedTileSet();

    for (unsigned int vertical = 0; vertical <= selectedTileSet.texture.width;
         vertical += tileWidth) {
        DrawLine(vertical, 0, vertical, selectedTileSet.texture.height, gridColor);
    }

    for (unsigned int horizontal = 0; horizontal <= selectedTileSet.texture.height;
         horizontal += tileHeight) {
        DrawLine(0, horizontal, selectedTileSet.texture.width, horizontal, gridColor);
    }
}

bool TileSet::isMouseInsideTileSetZone() const {
    return mousePosition.x > 0 && mousePosition.x < static_cast<float>(TILESET_AREA_WIDTH) &&
           mousePosition.y > TILESET_AREA_VERTICAL_POSITION && mousePosition.y < GetScreenHeight() - gui->getHeight();
}

bool TileSet::isMouseInsideTileSet() const {
    auto &selectedTileSet = getSelectedTileSet();
    return worldPositionTileSet.x > 0 && worldPositionTileSet.x < selectedTileSet.texture.width &&
           mousePosition.x < TILESET_AREA_WIDTH &&
           worldPositionTileSet.y > 0 && worldPositionTileSet.y < selectedTileSet.texture.height &&
           mousePosition.y < GetScreenHeight() - gui->getHeight();
}

void TileSet::zoomCamera(const float deltaTime) {
    if (GetMouseWheelMoveV().y != 0) {
        const Vector2 worldBeforeZoom = GetScreenToWorld2D(mousePosition, camera);

        camera.zoom += GetMouseWheelMoveV().y * 2 * deltaTime;

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

void TileSet::selectTile() {
    auto &selectedTileSet = getSelectedTileSet();
    const int tileX = worldPositionTileSet.x / tileWidth;
    const int tileY = worldPositionTileSet.y / tileHeight;
    const int selectedCell = tileY * selectedTileSet.texture.width / tileWidth + tileX;

    if (selectedTileSet.isAutoTiling) {
        const int autoTileBlock = selectedCell / 48;
        selectedTileSet.selectedTilePosition.x = 0;
        selectedTileSet.selectedTilePosition.y = autoTileBlock * 4 * tileHeight;
    } else {
        selectedTileSet.selectedTilePosition.x = tileX * tileWidth;
        selectedTileSet.selectedTilePosition.y = tileY * tileHeight;
        selectedTileSet.selectedTiles.clear();
        selectedTileSet.selectedTiles.push_back(selectedTileSet.selectedTilePosition);
    }
}

void TileSet::drawSelectedTile() const {
    auto &selectedTileSet = getSelectedTileSet();
    if (isDragging && selectedTileSet.isMultiSelecting) {
        const float x = fminf(selectedTileSet.selectionStart.x, selectedTileSet.selectionEnd.x);
        const float y = fminf(selectedTileSet.selectionStart.y, selectedTileSet.selectionEnd.y);
        const float width = fabsf(selectedTileSet.selectionEnd.x - selectedTileSet.selectionStart.x);
        const float height = fabsf(selectedTileSet.selectionEnd.y - selectedTileSet.selectionStart.y);

        DrawRectangleLinesEx({x, y, width, height}, 2.0f, SELECTED_TILE_COLOR);
        return;
    }

    if (!selectedTileSet.selectedTiles.empty()) {
        for (const auto &[x, y]: selectedTileSet.selectedTiles) {
            DrawRectangleLinesEx(
                {
                    x,
                    y,
                    static_cast<float>(tileWidth),
                    static_cast<float>(tileHeight)
                },
                2.0f,
                SELECTED_TILE_COLOR
            );
        }
    } else {
        DrawRectangleLinesEx(
            {
                static_cast<float>(selectedTileSet.selectedTilePosition.x),
                static_cast<float>(selectedTileSet.selectedTilePosition.y),
                static_cast<float>(tileWidth),
                static_cast<float>(tileHeight)
            }, 2.0f, SELECTED_TILE_COLOR
        );
    }
}

void TileSet::startDrag() {
    auto &selectedTileSet = getSelectedTileSet();
    isDragging = true;
    selectedTileSet.isMultiSelecting = false;
    selectedTileSet.selectionStart = worldPositionTileSet;
    selectedTileSet.selectionEnd = worldPositionTileSet;

    selectTile();
}

void TileSet::updateDrag() {
    if (!isMouseInsideTileSet()) return;

    auto &selectedTileSet = getSelectedTileSet();

    selectedTileSet.selectionEnd = worldPositionTileSet;

    const float diffX = fabs(selectedTileSet.selectionEnd.x - selectedTileSet.selectionStart.x);
    const float diffY = fabs(selectedTileSet.selectionEnd.y - selectedTileSet.selectionStart.y);

    if (diffX > tileWidth / 2 || diffY > tileHeight / 2) {
        selectedTileSet.isMultiSelecting = true;
    }
}

void TileSet::endDrag() {
    auto &selectedTileSet = getSelectedTileSet();
    isDragging = false;

    if (!selectedTileSet.isMultiSelecting && !selectedTileSet.isAutoTiling) return;

    const float x = fminf(selectedTileSet.selectionStart.x, selectedTileSet.selectionEnd.x);
    const float y = fminf(selectedTileSet.selectionStart.y, selectedTileSet.selectionEnd.y);
    const float width = fabsf(selectedTileSet.selectionEnd.x - selectedTileSet.selectionStart.x);
    const float height = fabsf(selectedTileSet.selectionEnd.y - selectedTileSet.selectionStart.y);

    int startTileX, startTileY, endTileX, endTileY;

    if (!selectedTileSet.isMultiSelecting) {
        startTileX = endTileX = floorf(selectedTileSet.selectionStart.x / tileWidth);
        startTileY = endTileY = floorf(selectedTileSet.selectionStart.y / tileHeight);
    } else {
        startTileX = floorf(x / tileWidth);
        startTileY = floorf(y / tileHeight);
        endTileX = ceilf((x + width) / tileWidth);
        endTileY = ceilf((y + height) / tileHeight);
    }

    const int maxTileX = selectedTileSet.texture.width / tileWidth;
    const int maxTileY = selectedTileSet.texture.height / tileHeight;

    startTileX = Clamp(startTileX, 0, maxTileX);
    startTileY = Clamp(startTileY, 0, maxTileY);
    endTileX = Clamp(endTileX, 0, maxTileX);
    endTileY = Clamp(endTileY, 0, maxTileY);

    selectedTileSet.selectedTiles.clear();

    if (selectedTileSet.isAutoTiling) {
        const int midTileX = (startTileX + endTileX) / 2;
        const int midTileY = (startTileY + endTileY) / 2;
        const int selectedCell = midTileY * selectedTileSet.texture.width / tileWidth + midTileX;

        const int autoTileBlock = selectedCell / 48;
        selectedTileSet.selectedTilePosition.x = 0;
        selectedTileSet.selectedTilePosition.y = autoTileBlock * 4 * tileHeight;

        selectedTileSet.selectedTiles.push_back(selectedTileSet.selectedTilePosition);
    } else {
        for (int row = startTileY; row < endTileY; row++) {
            for (int column = startTileX; column < endTileX; column++) {
                selectedTileSet.selectedTiles.push_back({
                    static_cast<float>(column * tileWidth),
                    static_cast<float>(row * tileHeight)
                });
            }
        }

        if (!selectedTileSet.selectedTiles.empty()) {
            selectedTileSet.selectedTilePosition = selectedTileSet.selectedTiles[0];
        }
    }
}
