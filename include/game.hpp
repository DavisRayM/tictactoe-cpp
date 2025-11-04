#ifndef GAME_HPP
#define GAME_HPP
#include "board.hpp"

class Game {
public:
  Game();
  ~Game();

  /// Display the current game board.
  void Display() const;

  /// Updates the current game generation; requests a move
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
    current = next;
    generation += 1;

    if (player == X)
      player = CIRCLE;
    else
      player = X;

    auto winState = current->WinState();
    switch (winState) {
    case CIRCLE_WIN || X_WIN || DRAW:
      live = false;
      break;
    default:
      break;
    }

    return winState;
  }
};
#endif
