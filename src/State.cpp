#include "../include/State.h"

State::State(): bg(), music() {
  this->quitRequested = false;
}

// pre-carregar os assets aqui?
void State::LoadAssets() { }

void State::Update(float dt) {
  // if user pressed the close button or alt+F4
  bool userWantsOff = SDL_QuitRequested();
  if (userWantsOff) {
    this->quitRequested = true;
    return;
  }  
}

void State::Render() {
  if (bg.IsOpen()) {
    this->bg.Render(0, 0);
  }
}
