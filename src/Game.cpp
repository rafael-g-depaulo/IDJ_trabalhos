#include <chrono>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include "../include/Game.h"
#include "../include/Resources.h"

// game instance
Game* Game::instance;

Game& Game::GetInstance() {
  if (Game::instance == nullptr) {
    cout << "Tried to call GetInstance before instantiating Game" << endl;
    exit(0);
  }
  return *Game::instance;
}

State& Game::GetState() {
  return *(this->state);
}

SDL_Renderer* Game::GetRenderer() {
  return (this->renderer);
}

void Game::Run() {
  auto previous_frame = chrono::steady_clock::now();
  auto current_frame = previous_frame;

  // cout << "started at time " << start_time.time_since_epoch().count() << endl;
  while (!this->state->QuitRequested()) {
    // calculate time since last frame and update current and previous frame
    previous_frame = current_frame;
    current_frame = chrono::steady_clock::now();
    auto deltaTime = chrono::duration_cast<chrono::milliseconds>(current_frame - previous_frame);
    // cout << deltaTime.count() << "ms ellapsed since last frame" << endl;

    state->Update((float) deltaTime.count());
    state->Render();
    SDL_RenderPresent(this->renderer);

    // get the time taken to update/render, and take that into account for frame delay
    auto after_render = chrono::steady_clock::now();
    auto calc_time = chrono::duration_cast<chrono::milliseconds>(after_render - current_frame);
    // add one beause 0.9ms get's rounded down to 0ms, and 1ms is better for our use case
    Uint32 c_time = (Uint32) calc_time.count() + 1;
    Uint32 frame_delay = c_time >= 33 ? 0 : 33 - c_time;

    // cout << "took " << c_time << "ms to calculate frame. will wait " << frame_delay << "ms until next frame is calculated" << endl;
    SDL_Delay(frame_delay);
  }

  // unload assets and empty caches
  Resources::ClearImages();
  Resources::ClearMusics();
  Resources::ClearSounds();
}

Game::Game(string title, int width, int height) {
  // if has already been instanced, log and crash
  if (Game::instance != nullptr) {
    cout << "Tentativa de instanciar Game quando já existe uma instancia" << endl;
    exit(0);
  }

  // set instance
  Game::instance = this;

  // initialice SDL, and crash if error
  int SDL_error = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
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
    cout << "Mix_Init não carregou todos os loaders pedidos. Bitmask carregada: " << Mix_error << endl;
    exit(0);
  }

  int Mix_audioError = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
  if (Mix_audioError != 0) {
    cout << "Mix_OpenAudio retornou com erro " << Mix_audioError << endl;
    exit(0);
  }
  Mix_AllocateChannels(32);

  Game::window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
  if (Game::window == nullptr) {
    cout << "Erro criando a janela" << endl;
    exit(0);
  }

  Game::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (Game::renderer == nullptr) {
    cout << "Erro renderizando a janela" << endl;
    exit(0);
  }

  this->state = new State();
}

Game::~Game() {
  cout << "desinstanciando Game" << endl;
  delete this->state;
  
  // a ordem importa. tem que ser na ordem inversa da inicialização
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  SDL_Quit();
}
