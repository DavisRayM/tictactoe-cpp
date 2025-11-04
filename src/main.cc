#include <ai.hpp>
#include <game.hpp>

int main(int argc, char **argv) {
  Game game;

  // Simulated Game
  do {
    game.Display();
  } while (game.Update(true));

  game.Display();

  return 0;
}
