#include <ai.hpp>
#include <game.hpp>
#include <iostream>

Move RequestMove(Game &game) {
  Move move(-1, -1);
  std::cout << "Enter x coordinate: ";
  std::cin >> move.x;

  std::cout << "Enter y coordinate: ";
  std::cin >> move.y;

  while (!game.IsValidMove(move)) {
    std::cout << "invalid coordinates.\n\n";

    std::cout << "Enter x coordinate: ";
    std::cin >> move.x;

    std::cout << "Enter y coordinate: ";
    std::cin >> move.y;
  }

  return move;
}

bool Update(Game &game, bool simulate) {
  Move move(-1, -1);
  bool showBoard = false;

  if (simulate)
    move = BestMove(game.CurrentBoard(), game.PlayerToken());
  else
    move = RequestMove(game);

  BoardWinState state = game.UpdateBoard(move);

  if (state == CIRCLE_WIN) {
    showBoard = true;
    std::cout << "O wins!\n";
  }
  if (state == X_WIN) {
    showBoard = true;
    std::cout << "X wins!\n";
  }
  if (state == DRAW) {
    showBoard = true;
    std::cout << "No one wins!\n";
  }

  if (showBoard)
    std::cout << game.Display();

  return game.IsLive();
}

int main(int argc, char **argv) {
  Game game;
  bool gameOngoing;
  bool simulate = false;

  // vs AI Game
  while (game.IsLive()) {
    std::cout << "\nPlayer " << game.PlayerDisplay() << "'s turn.\n";
    std::cout << game.Display();

    Update(game, simulate);
  }
  return 0;
}
