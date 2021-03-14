#ifndef music_h
#define music_h

#include <iostream>
#include "SDL2/SDL_mixer.h"

using namespace std;

class Music {
  public:
    Music();
    Music(string file);

    void Play(int times);
    void Stop(int msToStop);
    void Open(string file);
    bool IsOpen;

  private:
    Mix_Music* music;
};

#endif
