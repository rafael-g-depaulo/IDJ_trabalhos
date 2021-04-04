#include "../include/State.h"

State::State(): music("./assets/audio/music.mp3") {
  this->quitRequested = false;
  this->music.Play(-1);
  
  // initialize background
  auto bgGO = new GameObject();
  this->bg = new Sprite(*bgGO, "./assets/img/3.jpg");
  this->objectArray.push_back(unique_ptr<GameObject> (bgGO));
}

State::~State() {
  this->objectArray.clear();
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
  if (bg->IsOpen()) {
    this->bg->Render(0, 0);
  }
}
