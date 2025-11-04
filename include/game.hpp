#include "board.hpp"

class Game {
public:
  Game();
  ~Game();

  /// Display the current game board.
  bool display();
private:
  Board current;
  Token player;
};
