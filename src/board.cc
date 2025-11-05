#include <board.hpp>

static BoardWinState win_state(Token winner) {
  switch (winner) {
  case Token::EMPTY:
    return BoardWinState::ONGOING;
    break;
  case Token::CIRCLE:
    return BoardWinState::CIRCLE_WIN;
    break;
  case Token::X:
    return BoardWinState::X_WIN;
    break;
  }
}

bool Board::Play(int x, int y, Token player, Board *board) const {
  if (x < 0 || x >= 3 || y < 0 || y >= 3)
    // invalid coordinates
    return false;

  if (state[x][y] == Token::CIRCLE || state[x][y] == Token::X)
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
    return BoardWinState::DRAW;
  }

  return BoardWinState::ONGOING;
}

std::vector<Move> Board::ValidMoves() const {
  std::vector<Move> moves;

  for (int x = 0; x < 3; x++)
    for (int y = 0; y < 3; y++) {
      if (state[x][y] == Token::EMPTY)
        moves.push_back(Move(x, y));
    }

  return moves;
}

std::vector<std::array<Token, 3>> Board::GetLines() const {
  std::vector<std::array<Token, 3>> lines;

  /* Add row lines */
  lines.push_back({state[0][0], state[0][1], state[0][2]});
  lines.push_back({state[1][0], state[1][1], state[1][2]});
  lines.push_back({state[1][0], state[1][1], state[1][2]});

  /* Add column lines */
  lines.push_back({state[0][0], state[1][0], state[2][0]});
  lines.push_back({state[0][1], state[1][1], state[2][1]});
  lines.push_back({state[0][2], state[1][2], state[2][2]});

  /* Diagonal lines */
  lines.push_back({state[0][0], state[1][1], state[2][2]});
  lines.push_back({state[0][2], state[1][1], state[2][0]});

  return lines;
};
