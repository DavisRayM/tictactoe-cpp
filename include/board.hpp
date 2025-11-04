enum Token {
  CIRCLE=1,
  X,
};

struct Board {
  Token state[3][3];

  Board();
  ~Board();

  /// Updates the board state at position (x, y) to show the current `player`.
  /// Returns the new generation of the board with the updated state.
  ///
  /// pre: state[x][y] is not set.
  int play(int x, int y, Token player, Board *board);
};
