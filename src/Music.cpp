#include "../include/Music.h"
#include "../include/Resources.h"

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
  this->music = Resources::GetMusic(file);
}

void Music::Play(int times = -1) {
  if (IsOpen()) {
    Mix_PlayMusic(music, times);
  }
}

void Music::Stop(int msToStop) {
  Mix_FadeOutMusic(msToStop);
}
