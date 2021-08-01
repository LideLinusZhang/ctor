cmake_minimum_required(VERSION 3.19)
project(ctor)

set(CMAKE_CXX_STANDARD 14)

add_executable(ctor view.cc fairDice.cc loadedDice.cc game.cc
        player.cc random.h random.cc tile.cc vertex.cc geese.cc
        edge.cc randomMode.cc fileMode.cc boardFactory.cc
        controller.h controller.cc color.cc resourceType.cc
        board.cc boardPrinters.h boardPrinters.cc)