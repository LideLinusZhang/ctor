cmake_minimum_required(VERSION 3.19)
project(ctor)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Werror=vla")

add_executable(ctor view.cc fairDice.cc loadedDice.cc game.cc
        player.cc randomGen.cc tile.cc vertex.cc geese.cc
        edge.cc randomMode.cc fileMode.cc boardLayoutFactory.cc
        controller.cc color.cc resourceType.cc
        board.cc boardPrinters.h boardPrinters.cc main.cc buildingType.cc)