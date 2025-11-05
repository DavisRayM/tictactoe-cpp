cmake_minimum_required(VERSION 3.23)

project(TicTacToe)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 3.0.2
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM
)
FetchContent_MakeAvailable(SFML)

add_executable(TicTacToe)
target_sources(TicTacToe
  PRIVATE
    src/main.cc
)
target_compile_features(TicTacToe PRIVATE cxx_std_17)
target_link_libraries(TicTacToe
  PRIVATE
    LibTicTacToe
    SFML::Graphics
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
    include/ai.hpp

  PRIVATE
    src/game.cc
    src/board.cc
    src/ai.cc
)
set_target_properties(LibTicTacToe PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(tests)
