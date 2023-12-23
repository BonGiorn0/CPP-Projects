cmake_minimum_required(VERSION 3.10)

project(Tetris VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(main main.cpp Game.cpp Tile.cpp Shape.cpp)

#target_include_directories(main PUBLIC "${PROJECT_SOURCE_DIR}/Source")

target_link_libraries(main PUBLIC sfml-graphics sfml-window sfml-system)
