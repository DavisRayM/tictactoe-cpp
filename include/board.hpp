#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <array>

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

  /// Get the winning lines for the TicTacToe board.
  std::vector<std::array<Token, 3>> GetLines() const {
    std::vector<std::array<Token, 3>> lines;

    /* Add row lines */
    lines.push_back({state[0][0], state[0][1], state[0][2]});
    lines.push_back({state[1][0], state[1][1], state[1][2]});
    lines.push_back({state[1][0], state[1][1], state[1][2]});

    /* Add column lines */
    lines.push_back({state[0][0], state[1][0], state[2][0]});
    lines.push_back({state[0][1], state[1][1], state[2][1]});
    lines.push_back({state[0][2], state[1][2], state[2][2]});

    /* Diagonal lines */
    lines.push_back({state[0][0], state[1][1], state[2][2]});
    lines.push_back({state[0][2], state[1][1], state[2][0]});

    return lines;
  };
};

#endif
