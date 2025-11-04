#include <game.hpp>

int main(int argc, char** argv) {
  Game game;

  game.Display();
  while (game.Update()) {
    game.Display();
  }
  return 0;
}
