#include <ai.hpp>
#include <game.hpp>
#include <iostream>

/// Returns display character for a player token.
static char player_token(size_t token) {
  switch (token) {
  case CIRCLE:
    return 'O';
    break;
  case X:
    return 'X';
    break;
  default:
    return ' ';
    break;
  }
}

static Move RequestMove(Board *board, Token player) {
  int x, y;

  std::cout << "Player " << player_token(player) << "'s turn.\n";
  do {
    std::cout << "Enter x coordinate: ";
    std::cin >> x;

    std::cout << "Enter y coordinate: ";
    std::cin >> y;
  } while (!board->Play(x, y, player, nullptr));

  return Move(x, y);
}

Game::Game() {
  current = new Board;
  player = X;
  generation = 0;
  live = true;
}

Game::~Game() {
  delete current;
  current = nullptr;
}

void Game::Display() const {
  std::cout << "-------\n";

  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      std::cout << "|" << player_token(current->state[r][c]);
    }
    std::cout << "|\n-------\n";
  }
}

bool Game::Update(bool simulate) {
  int x, y;
  Board *next = new Board;
  Move move(-1, -1);
  if (simulate)
    move = BestMove(current, player);
  else
    move = RequestMove(current, player);

  BoardWinState state = UpdateBoard(move);
  std::cout << "State: " << state << " Live: " << this->live << "\n";

  if (state == CIRCLE_WIN)
    std::cout << "O wins!\n";
  if (state == X_WIN)
    std::cout << "X wins!\n";
  if (state == DRAW)
    std::cout << "No one wins!\n";

  return this->live;
}
