#include "../include/Game.h"

#include <iostream>
#include <unistd.h>

using namespace std;

int main(int argc, char** argv) {
  // this is just to stop the "unused parameter" warnings
  if (argc == 1) {
    cout << argv[0];
  }

  Game *game = new Game("Teste", 1024, 600);
  *game = Game::GetInstance();
  game->Run();
  delete game;

  return 0;
}
