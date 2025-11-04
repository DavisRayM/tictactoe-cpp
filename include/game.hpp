#ifndef GAME_HPP
#define GAME_HPP
#include "board.hpp"

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
  void Display() const;

  /// Updates the current game generation; requests or simulates a move
  /// from the player and transitions to next state. Returns whether
  /// the game is still live.
  ///
  /// pre: live is true
  /// post: updates generation and live
  bool Update(bool simulate = false);

private:
  Board *current;
  Token player;
  unsigned int generation;
  bool live;

  /// Updates current board generation.
  ///
  /// pre: move is a valid move for the current generation
  BoardWinState UpdateBoard(Move move) {
    Board *next = new Board;
    if (!current->Play(move.x, move.y, player, next))
      return ERROR;

    delete current;
    this->current = next;
    this->generation += 1;

    if (player == X)
      this->player = CIRCLE;
    else
      this->player = X;

    auto winState = current->WinState();
    switch (winState) {
    case CIRCLE_WIN:
    case X_WIN:
    case DRAW:
    case ERROR:
      this->live = false;
      break;
    default:
      break;
    }

    return winState;
  }
};
#endif
