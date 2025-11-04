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
  BoardWinState winner = ONGOING;

  /* Check rows for any winner */
  for (int x = 0; x < 3 && winner == ONGOING; x++) {
    int start = state[x][0];
    winner = win_state(start);

    for (int y = 1; y < 3; y++) {
      if (start != state[x][y]) {
        winner = ONGOING;
        break;
      }
    }
  }

  /* Check columns for any winner */
  for (int y = 0; y < 3 && winner == ONGOING; y++) {
    int start = state[0][y];
    winner = win_state(start);

    for (int x = 1; x < 3; x++) {
      if (start != state[x][y]) {
        winner = ONGOING;
        break;
      }
    }
  }

  /* Check Left-Right Diagonal for any winner */
  if (winner == ONGOING) {
    int start = state[0][0];
    winner = win_state(start);

    for (int x = 1, y = 1; x < 3 && y < 3; x++, y++) {
      if (start != state[x][y]) {
        winner = ONGOING;
        break;
      }
    }
  }

  /* Check Right-Left Diagonal for any winner */
  if (winner == ONGOING) {
    int start = state[2][0];
    winner = win_state(start);

    for (int x = 1, y = 1; x >= 0 && y < 3; x--, y++) {
      if (start != state[x][y]) {
        winner = ONGOING;
        break;
      }
    }
  }

  if (ValidMoves().size() == 0)
    winner = DRAW;

  return winner;
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
