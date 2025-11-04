#include <board.hpp>

static BoardWinState win_state(int winner) {
  switch (winner) {
  case 0:
    return ONGOING;
    break;
  case 1:
    return CIRCLE_WIN;
    break;
  case 2:
    return X_WIN;
    break;
  default:
    return ERROR;
    break;
  }
}

bool Board::Play(int x, int y, Token player, Board *board) const {
  if (x < 0 || x >= 3 || y < 0 || y >= 3)
    // invalid coordinates
    return false;

  if (state[x][y] == CIRCLE || state[x][y] == X)
    // position already occupied
    return false;

  if (board == nullptr)
    // no where to save
    return true;

  // Update `board`
  for (int r = 0; r < 3; r++)
    for (int c = 0; c < 3; c++)
      board->state[r][c] = state[r][c];

  board->state[x][y] = player;
  return true;
}

BoardWinState Board::WinState() const {
  for (auto &line : GetLines()) {
    bool win = true;

    for (int i = 1; i < 3; i++) {
      if (line[i - 1] != line[i])
        win = false;
    }

    if (win)
      return win_state(line[0]);
  }

  if (ValidMoves().empty()) {
    return DRAW;
  }

  return ONGOING;
}

std::vector<Move> Board::ValidMoves() const {
  std::vector<Move> moves;

  for (int x = 0; x < 3; x++)
    for (int y = 0; y < 3; y++) {
      if (state[x][y] == 0)
        moves.push_back(Move(x, y));
    }

  return moves;
}
