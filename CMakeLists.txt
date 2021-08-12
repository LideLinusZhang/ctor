cmake_minimum_required(VERSION 3.19)
project(constructor)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Werror=vla -g3")

add_executable(constructor view.cc fairDice.cc loadedDice.cc game.cc
        player.cc randomGen.cc tile.cc vertex.cc geese.cc
        edge.cc randomMode.cc fileMode.cc boardLayoutFactory.cc
        controller.cc color.cc resourceType.cc adjacencyTables.h errorType.h
        board.cc boardPrinters.h boardPrinters.cc main.cc buildingType.cc)