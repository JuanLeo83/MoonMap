cmake_minimum_required(VERSION 3.31)
project(MoonMap)
include(FetchContent)

set(CMAKE_CXX_STANDARD 17)

set(IMGUI_VERSION 1.91.8)
add_executable(MoonMap main.cpp
        src/tileset/TileSet.h
        src/tileset/TileSetCell.h
        src/tileset/TileSet.cpp
        src/Constants.h
)

FetchContent_Declare(
        imgui
        URL https://github.com/ocornut/imgui/archive/refs/tags/v${IMGUI_VERSION}-docking.tar.gz
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
        glfw
        URL https://github.com/glfw/glfw/archive/refs/tags/3.3.8.tar.gz
)
FetchContent_MakeAvailable(glfw)

find_package(OpenGL REQUIRED)

add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

add_library(ImGuiFileDialog STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/ImGuiFileDialog/ImGuiFileDialog.cpp
)

target_include_directories(ImGuiFileDialog PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${imgui_SOURCE_DIR}
)

target_link_libraries(imgui PUBLIC glfw OpenGL::GL)

target_sources(MoonMap PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/rlImGui/rlImGui.cpp
)

find_library(RAYLIB_LIBRARY
        NAMES raylib
        PATHS /opt/homebrew/lib /usr/local/lib
        REQUIRED
)

find_path(RAYLIB_INCLUDE_DIR
        NAMES raylib.h
        PATHS /opt/homebrew/include /usr/local/include
        REQUIRED
)

target_include_directories(MoonMap PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/engine
        ${RAYLIB_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/rlImGui
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/ImGuiFileDialog
)

target_link_libraries(MoonMap PRIVATE
        ${RAYLIB_LIBRARY}
        "-framework OpenGL"
        "-framework IOKit"
        "-framework Cocoa"
        "-framework CoreVideo"
        imgui
        ImGuiFileDialog
)

target_compile_features(MoonMap PRIVATE cxx_std_17)
