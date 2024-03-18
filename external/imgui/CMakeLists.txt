cmake_minimum_required(VERSION 3.28)
project(imgui)

include(FetchContent)
FetchContent_Declare(
  imgui
  GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
  GIT_TAG "v1.90.4-docking"
)
FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC)
target_sources(
  imgui
  PRIVATE
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(
  imgui
  PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
target_include_directories(
  imgui
  PRIVATE
    $<TARGET_PROPERTY:SDL2,INTERFACE_INCLUDE_DIRECTORIES>
)

