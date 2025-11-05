SET(TEST_SOURCES
  game_test.cc
  board_test.cc
)

include(FetchContent)
FetchContent_Declare(Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.8.1
)
FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests
  PRIVATE
    Catch2::Catch2WithMain
    LibTicTacToe
)

include(CTest)
enable_testing()
include(Catch)
catch_discover_tests(tests)
