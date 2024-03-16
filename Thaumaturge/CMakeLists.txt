cmake_minimum_required(VERSION 3.28)
project(Thaumaturge)

if(WIN32)
  add_executable(Thaumaturge WIN32)
else()
  add_executable(Thaumaturge)
endif()
target_sources(
  Thaumaturge
  PRIVATE
    Main.cpp
)
target_link_libraries(
  Thaumaturge
  PRIVATE
    Numina
    Numain
)

add_custom_target(
  editor
  COMMAND Thaumaturge
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

