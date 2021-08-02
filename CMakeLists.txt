cmake_minimum_required(VERSION 3.19)
project(ctor)

set(CMAKE_CXX_STANDARD 14)

add_executable(ctor view/view.cc controller/dices/fairDice.cc controller/dices/loadedDice.cc controller/game.cc
        models/player.cc random.h random.cc models/tile.cc models/vertex.cc models/geese.cc
        models/edge.cc boardFactory/randomMode.cc boardFactory/fileMode.cc boardFactory/boardFactory.cc
        controller/controller.h controller/controller.cc color.cc resourceType.cc
        models/board.cc view/boardPrinters.h view/boardPrinters.cc)