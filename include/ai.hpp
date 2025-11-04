#ifndef AI_HPP
#define AI_HPP
#include "board.hpp"
#include <climits>
#include <stdexcept>

namespace {
int InnerMiniMax(Board *board, int depth, bool maximize,
                        Token currentPlayer, Token maximizingPlayer) {
  Token nextPlayer = (currentPlayer == CIRCLE) ? X : CIRCLE;

  if (depth == 0 || board->ValidMoves().empty()) {
    switch (board->WinState()) {
    case CIRCLE_WIN:
      return (maximizingPlayer == CIRCLE) ? 1 : -1;
    case X_WIN:
      return (maximizingPlayer == X) ? 1 : -1;
    case DRAW:
      return 0;
    default:
      return 0;
    }
  }

  int bestScore = maximize ? INT_MIN : INT_MAX;
  for (auto &move : board->ValidMoves()) {
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


static Move BestMove(Board *board, Token player, int depth = 5) {
  int bestScore = INT_MIN;
  Move bestMove(-1, -1);

  for (auto &move: board->ValidMoves()) {
    Board next;
    if (!board->Play(move.x, move.y, player, &next))
      continue;

    int score = InnerMiniMax(&next, depth - 1, false, (player == CIRCLE) ? X : CIRCLE, player);
    if (score > bestScore) {
      bestScore = score;
      bestMove = move;
    }
  }

  return bestMove;
}
#endif
