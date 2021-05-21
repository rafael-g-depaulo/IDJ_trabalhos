#ifndef resources_h
#define resources_h

#include <unordered_map>

#include "Sprite.h"
#include "Music.h"

using namespace std;

class Resources {
  public:
    static SDL_Texture* GetImage(string file);
    static Mix_Music* GetMusic(string file);
    static Mix_Chunk* GetSound(string file);
    static void ClearImages();
    static void ClearMusics();
    static void ClearSounds();

  private:
    static unordered_map<string, SDL_Texture*> imageTable;
    static unordered_map<string, Mix_Music*> musicTable;
    static unordered_map<string, Mix_Chunk*> soundTable;
};

#endif
