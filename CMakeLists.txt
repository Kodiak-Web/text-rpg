cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
project(Text_rpg)
add_executable(HotelMalum src/main.cpp src/combat.cpp src/combatActions.cpp src/combatEntities.cpp) #every file not #included must be added to compilation this way
