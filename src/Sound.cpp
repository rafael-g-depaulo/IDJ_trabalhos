#include "../include/Sound.h"
#include "../include/Resources.h"

using namespace std;

Sound::Sound(GameObject& associated): Component(associated) {
  this->chunk = nullptr;
}

// Sound::Sound(GameObject& associated, string file): Component(associated) {
Sound::Sound(GameObject& associated, string file): Sound(associated) {
  this->Open(file);
}

Sound::~Sound() {
  if (this->chunk != nullptr)
    this->Stop(0);
}

void Sound::Play(int times) {
  // this -1 means "use whatever channel is available"
  int timesLooped = times - 1;
  this->channel = Mix_PlayChannel(-1, this->chunk, timesLooped);
}

void Sound::Stop(int msToStop) {
  // TODO: add delay with msToStop
  if (msToStop == 0) {}
  if (this->chunk != nullptr) {
    Mix_HaltChannel(this->channel);
  }
}

void Sound::Open(string file) {
  this->chunk = Resources::GetSound(file);
}

bool Sound::IsOpen() { return chunk != nullptr; }
bool Sound::Is(string type) { return type == "Sound"; }
void Sound::Update(float dt) { if (dt) {} }
void Sound::Render() {}
