#include "../include/State.h"

State::State(): bg("./assets/img/3.jpg"), music() {
  this->quitRequested = false;
}

// pre-carregar os assets aqui?
void State::LoadAssets() { }

void State::Update(float dt) {
  // i have no idea what dt if for this stops the "unuser parameter" warning
  if (dt != 0) { cout << "State::Update() with dt != 0" << endl; }

  // if user pressed the close button or alt+F4
  bool userWantsOff = SDL_QuitRequested();
  if (userWantsOff) {
    this->quitRequested = true;
    return;
  }  
}

bool State::QuitRequested() {
  return this->quitRequested;
}

void State::Render() {
  if (bg.IsOpen()) {
    this->bg.Render(0, 0);
  }
}
