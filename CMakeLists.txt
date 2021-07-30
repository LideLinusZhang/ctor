cmake_minimum_required(VERSION 3.19)
project(ctor)

set(CMAKE_CXX_STANDARD 14)

add_executable(ctor errorType.h view.cc dice.h fairDice.h loadedDice.h game.h player.h color.h resourceType.h board.h tile.h geese.h vertex.h buildingType.h edge.h fileMode.h boardFactory.h randomMode.h fairDice.cc)