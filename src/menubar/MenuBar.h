#pragma once
#include <functional>


class MenuBar {
    int mapWidth = 0;
    std::function<void(int)> onMapWidthChanged;

    int mapHeight = 0;
    std::function<void(int)> onMapHeightChanged;

    void drawMenuBar() const;

    void drawMapWidthSlider();

    void drawMapHeightSlider();

public:
    explicit MenuBar(std::function<void(int)> onWidthChangedCallback = nullptr,
                     std::function<void(int)> onHeightChangedCallback = nullptr);

    void draw();

    int getValue() const { return mapWidth; }
    void setValue(const int value) { mapWidth = value; }
};
