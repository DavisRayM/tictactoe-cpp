cmake_minimum_required(VERSION 3.23)

project(TicTacToe)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(TicTacToe)
target_sources(TicTacToe
  PRIVATE
    src/main.cc
)
target_link_libraries(TicTacToe
  PRIVATE
    LibTicTacToe
)

add_library(LibTicTacToe)
target_sources(LibTicTacToe
  PUBLIC
  FILE_SET publicHeaders
  TYPE HEADERS
  BASE_DIRS
    include/
  FILES
    include/board.hpp
    include/game.hpp
)
set_target_properties(LibTicTacToe PROPERTIES LINKER_LANGUAGE CXX)
