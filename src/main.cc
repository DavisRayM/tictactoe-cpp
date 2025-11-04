#include <game.hpp>
#include <ai.hpp>

int main(int argc, char** argv) {
  Game game;

  // Fully AI Game
  game.Display();
  while (game.Update(true)) {
    game.Display();
  }
  return 0;
}
