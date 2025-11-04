#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

enum Token {
  CIRCLE = 1,
  X,
};

enum BoardWinState {
  ONGOING = 0,
  CIRCLE_WIN = 1,
  X_WIN = 2,
  DRAW = 3,
  ERROR = 4,
};

struct Move {
  int x;
  int y;

  Move(int x, int y) {
    this->x = x;
    this->y = y;
  }
};

struct Board {
  Token state[3][3];

  /// Simulates the player move based on current board state.
  /// Updates the memory stored at `board`. Returns a boolean on whether process
  /// was succesful.
  ///
  /// pre: state[x][y] is not set.
  bool Play(int x, int y, Token player, Board *board) const;

  /// Returns the current win state of the board.
  BoardWinState WinState() const;

  /// Populates `moves` with the current valid moves. Previous pointer is not
  /// cleaned up as such implementation should handle.
  std::vector<Move> ValidMoves() const;
};

#endif
