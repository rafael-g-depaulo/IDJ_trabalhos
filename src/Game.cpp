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

  cout << endl << "Inicializando..." << endl;

  int loaderMask = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
  int IMG_error = IMG_Init(loaderMask);
  if (IMG_error != loaderMask) { 
    cout << "IMG_Init não carregou todos os loaders pedidos. Bitmask carregada: " << IMG_error << endl;
    exit(0);
  }

  int Mix_error = Mix_Init(MIX_INIT_OGG);
  if (Mix_error != MIX_INIT_OGG) { 
    cout << "Mix_Init não carregou todos os loaders pedidos. Bitmask carregada: " << MIX_INIT_OGG << endl;
    exit(0);
  }

  int Mix_audioError = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
  if (Mix_audioError != 0) {
    cout << "Mix_OpenAudio retornou com erro " << Mix_audioError << endl;
    exit(0);
  }
  Mix_AllocateChannels(32);

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
