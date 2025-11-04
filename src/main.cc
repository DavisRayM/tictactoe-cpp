#include <ai.hpp>
#include <game.hpp>

int main(int argc, char **argv) {
  Game game;
  bool gameOngoing;
  bool simulate = false;

  // vs AI Game
  game.Display();
  do {
    gameOngoing = game.Update(simulate);
    simulate = !simulate;
    game.Display();
  } while (gameOngoing);

  return 0;
}
