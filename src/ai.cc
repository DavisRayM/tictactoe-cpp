#include <ai.hpp>
#include <climits>
#include <stdexcept>

namespace {
int EvaluateBoard(Board *board, Token maximizePlayer) {
  Token opp = (maximizePlayer == Token::CIRCLE) ? Token::X : Token::CIRCLE;
  int score = 0;

  auto lines = board->GetLines();
  for (auto &line : lines) {
    int maxCount = 0, oppCount = 0, emptyCount = 0;

    for (auto cell : line) {
      if (cell == maximizePlayer)
        maxCount++;
      else if (cell == opp)
        oppCount++;
      else
        emptyCount++;
    }

    if (maxCount == 2 && emptyCount == 1)
      score += 10;
    if (oppCount == 2 && emptyCount == 1)
      score -= 10;
  }

  for (int r = 0; r < 3; r++)
    for (int c = 0; c < 3; c++) {
      if (board->state[r][c] == maximizePlayer)
        score += 1;
      else if (board->state[r][c] != Token::EMPTY)
        score -= 1;
    }

  return score;
}

int InnerMiniMax(Board *board, int depth, bool maximize, Token currentPlayer,
                 Token maximizingPlayer) {
  Token nextPlayer =
      (currentPlayer == Token::CIRCLE) ? Token::X : Token::CIRCLE;
  auto moves = board->ValidMoves();

  if (depth == 0 || moves.empty()) {
    switch (board->WinState()) {
    case BoardWinState::CIRCLE_WIN:
      return (maximizingPlayer == Token::CIRCLE) ? 1000 : -1000;
    case BoardWinState::X_WIN:
      return (maximizingPlayer == Token::X) ? 1000 : -1000;
    case BoardWinState::DRAW:
      return 0;
    default:
      return EvaluateBoard(board, maximizingPlayer);
    }
  }

  int bestScore = maximize ? INT_MIN : INT_MAX;
  for (auto &move : moves) {
    Board next;
    if (!board->Play(move.x, move.y, currentPlayer, &next))
      throw std::runtime_error("Invalid move!");

    int score =
        InnerMiniMax(&next, depth - 1, !maximize, nextPlayer, maximizingPlayer);
    bestScore =
        maximize ? std::max(bestScore, score) : std::min(bestScore, score);
  }
  return bestScore;
}
} // namespace

Move BestMove(Board *board, Token player, int depth) {
  int bestScore = INT_MIN;
  Move bestMove(-1, -1);

  for (auto &move : board->ValidMoves()) {
    Board next;
    if (!board->Play(move.x, move.y, player, &next))
      continue;

    int score = InnerMiniMax(
        &next, depth - 1, false,
        (player == Token::CIRCLE) ? Token::X : Token::CIRCLE, player);
    if (score > bestScore) {
      bestScore = score;
      bestMove = move;
    }
  }

  return bestMove;
}
