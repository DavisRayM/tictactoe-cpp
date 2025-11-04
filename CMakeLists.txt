cmake_minimum_required(VERSION 3.23)

project(TicTacToe)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(TicTacToe)

target_sources(TicTacToe
  PRIVATE
    src/main.cc
)
