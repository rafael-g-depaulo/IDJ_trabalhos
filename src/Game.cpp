#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include "../include/Game.h"

// game instance
Game* Game::instance;

Game& Game::GetInstance() {
  if (Game::instance == nullptr) {
    cout << "Tried to call GetInstance before instantiating Game" << endl;
    exit(0);
  }
  return *Game::instance;

  // // if instance already exists
  // if (Game::instance != nullptr)
  //   return *Game::instance;

  // // else, instantiate it
  // Game::instance = new Game("", 100, 100);
  // return *Game::instance;
}

Game::Game(string title, int width, int height) {
  // if has already been instanced, log and crash
  if (Game::instance != nullptr) {
    cout << "Tentativa de instanciar Game quando já existe uma instancia" << endl;
    exit(0);
  }

  // set instance
  instance = this;

  // initialice SDL, and crash if error
  // int SDL_error = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
  int SDL_error = SDL_Init( SDL_INIT_AUDIO | SDL_INIT_TIMER);
  if (SDL_error != 0) {
    cout << "SDL_Init retornou com erro " << SDL_error << ": " << SDL_GetError() << endl;
    exit(0);
  }

  cout << "Inicializando..." << endl;

  // The following code crashes in WSL because of complicated reasons.
  // I will change to a Windows development environment and then un-comment it

  // int IMG_error = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
  // if (IMG_error != 0) { 
  //   cout << "IMG_Init retornou com erro " << IMG_error << ": " << SDL_GetError() << endl;
  //   exit(0);
  // }

  // int Mix_error = Mix_Init(MIX_INIT_OGG);
  // if (Mix_error != 0) { 
  //   cout << "Mix_Init retornou com erro " << Mix_error << ": " << SDL_GetError() << endl;
  //   exit(0);
  // }

  // Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
  // Mix_AllocateChannels(32);

  Game::window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
  if (!window) {
    cout << "Erro criando a janela" << endl;
    exit(0);
  }

  Game::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Game::~Game() {
  cout << "desinstanciando Game" << endl;
  delete this->state;
  
  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
