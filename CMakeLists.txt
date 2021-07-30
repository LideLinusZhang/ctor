cmake_minimum_required(VERSION 3.19)
project(ctor)

set(CMAKE_CXX_STANDARD 14)

add_executable(ctor view.cc fairDice.cc loadedDice.cc game.cc player.cc random.h random.cc)