#include "../include/Sound.h"

using namespace std;

Sound::Sound(GameObject& associated): Component(associated) {
  // this->associated = associated;
  this->chunk = nullptr;
}

// Sound::Sound(GameObject& associated, string file): Component(associated) {
Sound::Sound(GameObject& associated, string file): Sound(associated) {
  this->Open(file);
}

Sound::~Sound() {
  if (this->chunk != nullptr) {
    this->Stop(0);
    Mix_FreeChunk(this->chunk);
  }
}

// !IMPORTANT
// TODO: fix sound play (not working)
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
  const auto chunk = Mix_LoadWAV(file.c_str());
  if (chunk == nullptr) {
    cout << "Mix_LoadWAV não carregou o arquivo de áudio pedido" << endl;
    exit(0);
    return;
  }

  this->chunk = chunk;
}

bool Sound::IsOpen() { return chunk != nullptr; }
bool Sound::Is(string type) { return type == "Sound"; }
void Sound::Update(float dt) { if (dt) {} }
void Sound::Render() {}
