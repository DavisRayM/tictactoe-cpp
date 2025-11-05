#include <ai.hpp>
#include <game.hpp>

namespace {
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
} // namespace

std::string Game::Display() const {
  std::string out = "";
  out += "\n-------\n";

  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 3; c++) {
      out += "|";
      out += player_token(current->state[r][c]);
    }
    out += "|\n-------\n";
  }

  return out;
}

BoardWinState Game::UpdateBoard(Move move) {
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

char Game::PlayerDisplay() const { return player_token(player); }

Token Game::PlayerToken() const { return player; }

Board *const Game::CurrentBoard() const { return current; }

bool Game::IsValidMove(Move move) const {
  return current->Play(move.x, move.y, player, nullptr);
}

bool Game::IsLive() const { return live; }
