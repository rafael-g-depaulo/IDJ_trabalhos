#include "Game.h"

// used for the temporary sleep call
#include <unistd.h>

// int main(int argc, char** argv) {
int main() {
  Game *game = new Game("Teste", 1024, 600);
  *game = Game::GetInstance();

  // sleep to keep window open for 3s
  sleep(3);
}
