cmake_minimum_required(VERSION 3.28)
project(glad)

add_library(glad STATIC)
target_sources(
  glad
  PRIVATE
    src/gl.c
)
set_target_properties(
  glad
  PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
target_include_directories(
  glad
  PUBLIC
    include
)

