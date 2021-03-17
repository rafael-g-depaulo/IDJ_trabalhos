#include "../include/Game.h"

// used for the temporary sleep call
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

  delete game;
  cout << "Press ENTER to exit program..." << endl;
  getchar();


  return 0;
}
