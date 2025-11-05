#include <ai.hpp>
#include <game.hpp>
#include <iostream>

Move RequestMove(Game &game) {
  Move move;
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
  Move move;
  bool showBoard = false;

  if (simulate)
    move = BestMove(game.CurrentBoard(), game.PlayerToken());
  else
    move = RequestMove(game);

  BoardWinState state = game.UpdateBoard(move);

  if (state == BoardWinState::CIRCLE_WIN) {
    showBoard = true;
    std::cout << "O wins!\n";
  }
  if (state == BoardWinState::X_WIN) {
    showBoard = true;
    std::cout << "X wins!\n";
  }
  if (state == BoardWinState::DRAW) {
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
    simulate = !simulate;
  }
  return 0;
}
