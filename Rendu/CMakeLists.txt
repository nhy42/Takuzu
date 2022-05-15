cmake_minimum_required(VERSION 3.21)
project(Takuzu C)

set(CMAKE_C_STANDARD 99)

add_executable(Takuzu main.c grid.c grid.h interaction.c interaction.h builtinGrids.h autosolve.c autosolve.h)
