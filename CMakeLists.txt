cmake_minimum_required(VERSION 3.28)
project(Thauma-Tools)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

include(FetchContent)
FetchContent_Declare(
  SDL2
  GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
  GIT_TAG "release-2.30.1"
)
FetchContent_MakeAvailable(
  SDL2
)

add_subdirectory(external/glad)
add_subdirectory(external/imgui)

add_subdirectory(Numina)
add_subdirectory(Thaumaturge)
 
