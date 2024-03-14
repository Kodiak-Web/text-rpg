cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
project(Text_rpg)
add_executable(GameTitle src/main.cpp src/globalstate.cpp src/combat.cpp ) #every file not #included must be added to compilation this way
