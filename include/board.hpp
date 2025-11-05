#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <vector>

enum class Token {
  EMPTY = 0,
  CIRCLE,
  X,
};

enum class BoardWinState {
  ONGOING = 0,
  CIRCLE_WIN = 1,
  X_WIN = 2,
  DRAW = 3,
  ERROR = 4,
};

struct Move {
  int x;
  int y;

  Move() : x(-1), y(-1) {}
  Move(int x, int y) : x(x), y(y) {}
};

struct Board {
  Token state[3][3] = {
      {Token::EMPTY, Token::EMPTY, Token::EMPTY},
      {Token::EMPTY, Token::EMPTY, Token::EMPTY},
      {Token::EMPTY, Token::EMPTY, Token::EMPTY},
  };

  /// Simulates the player move based on current board state.
  /// Updates the memory stored at `board`. Returns a boolean on whether process
  /// was succesful.
  ///
  /// pre: state[x][y] is not set.
  bool Play(int x, int y, Token player, Board* board) const;

  /// Returns the current win state of the board.
  BoardWinState WinState() const;

  /// Populates `moves` with the current valid moves. Previous pointer is not
  /// cleaned up as such implementation should handle.
  std::vector<Move> ValidMoves() const;

  /// Get the winning lines for the TicTacToe board.
  std::vector<std::array<Token, 3>> GetLines() const;
};

#endif
