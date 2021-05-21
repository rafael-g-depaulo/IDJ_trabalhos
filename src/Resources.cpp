#include "../include/Resources.h"
#include "../include/Game.h"

using namespace std;

unordered_map<string, SDL_Texture*> Resources::imageTable;
unordered_map<string, Mix_Music*> Resources::musicTable;
unordered_map<string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage(string file) {
  // if image is already in cache, return it
  auto cachedImage = Resources::imageTable.find(file);
  if (cachedImage != Resources::imageTable.end())
    return cachedImage->second;

  // load image, save to cache and return it
  auto image = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
  Resources::imageTable.insert(make_pair(file, image));
  return image;
}

Mix_Music* Resources::GetMusic(string file) {
  // if music is already in cache, return it
  auto cachedMusic = Resources::musicTable.find(file);
  if (cachedMusic != Resources::musicTable.end())
    return cachedMusic->second;

  // load music, save to cache and return it
  auto music = Mix_LoadMUS(file.c_str());
  
  // crash if loading error
  if (music == nullptr) {
    cout << "Erro ao carregar musica \"" << file << "\"" << endl;
    cout << "Error: " << SDL_GetError() << endl;
    exit(0);
  }

  Resources::musicTable.insert(make_pair(file, music));
  return music;
}

Mix_Chunk* Resources::GetSound(string file) {
  // if sound is already in cache, return it
  auto cachedSound = Resources::soundTable.find(file);
  if (cachedSound != Resources::soundTable.end())
    return cachedSound->second;

  // load sound, save to cache and return it
  auto sound = Mix_LoadWAV(file.c_str());
  if (sound == nullptr) {
    cout << "Mix_LoadWAV não carregou o arquivo de áudio pedido" << endl;
    exit(0);
  }

  Resources::soundTable.insert(make_pair(file, sound));
  return sound;
}

void Resources::ClearImages() {
  // destroy all image textures, then delete imageTable
  cout << "Clearing image cache:" << endl;
  for (auto pair : Resources::imageTable) {
    cout << "\t- clearing texture \"" << pair.first << "\" from cache." << endl;
    SDL_DestroyTexture(pair.second);
  }
  cout << "\t- Image cache cleared." << endl;

  Resources::imageTable.clear();
}

void Resources::ClearMusics() {
  // stop all music, then delete musicTable
  cout << "Clearing music cache:" << endl;
  for (auto pair : Resources::musicTable) {
    cout << "\t- clearing music \"" << pair.first << "\" from cache." << endl;
    delete pair.second;
  }
  Mix_FadeOutMusic(0);
  cout << "\t- Music cache cleared." << endl;

  Resources::musicTable.clear();
}

void Resources::ClearSounds() {
  // stop all sound, then delete soundTable
  cout << "Clearing sound cache:" << endl;
  for (auto pair : Resources::soundTable) {
    cout << "\t- clearing sound \"" << pair.first << "\" from cache." << endl;
    Mix_FreeChunk(pair.second);
  }
  cout << "\t- sound cache cleared." << endl;

  Resources::soundTable.clear();
}
