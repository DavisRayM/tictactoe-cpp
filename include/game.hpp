#ifndef GAME_HPP
#define GAME_HPP
#include "board.hpp"
#include <string>

class Game {
public:
  Game() {
    current = new Board;
    player = X;
    generation = 0;
    live = true;
  }

  ~Game() {
    delete current;
    current = nullptr;
    generation = 0;
    live = false;
    player = X;
  }

  /// Display the current game board.
  std::string Display() const;

  /// Updates current board generation.
  ///
  /// pre: move is a valid move for the current generation
  BoardWinState UpdateBoard(Move move);

  /// Returns current player display token.
  char PlayerDisplay() const;

  /// Returns current player token.
  Token PlayerToken() const;

  /// Returns a read only pointer to the underlying
  /// board.
  Board *const CurrentBoard() const;

  /// Returns whether the game is live.
  bool IsLive() const;

  /// Returns whether the move is valid
  bool IsValidMove(Move move) const;

private:
  Board *current;
  Token player;
  unsigned int generation;
  bool live;
};
#endif
