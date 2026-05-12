cmake_minimum_required(VERSION 3.10)

project(MyApp)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(app
    Test.cpp
    game_management/board.cpp
    game_management/piece.cpp
    game_management/king.cpp
    game_management/rook.cpp
    game_management/queen.cpp
    game_management/bishop.cpp
    game_management/knight.cpp
)