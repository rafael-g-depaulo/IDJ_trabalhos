#include "../include/Music.h"

Music::Music() {
  this->music = nullptr;
}

Music::Music(string file) {
  this->music = nullptr;
  this->Open(file);
}

bool Music::IsOpen() {
  return music != nullptr;
}

void Music::Open(string file) {
  // cout << "loading music \"" << file << "\"" << endl;
  this->music = Mix_LoadMUS(file.c_str());

  if (!this->IsOpen()) {
    cout << "Erro ao carregar musica" << endl;
    cout << "Error: " << SDL_GetError() << endl;
  }
}

void Music::Play(int times = -1) {
  if (IsOpen()) {
    Mix_PlayMusic(music, times);
  }
}

void Music::Stop(int msToStop) {
  Mix_FadeOutMusic(msToStop);
}
