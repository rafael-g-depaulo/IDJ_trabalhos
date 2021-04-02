#ifndef sound_h
#define sound_h

#include "SDL2/SDL_mixer.h"

#include "./GameObject.h"
#include "./Component.h"

class Sound : Component {
  public:
    Sound(GameObject& associated);
    Sound(GameObject& associated, std::string file);
    ~Sound();

    void Play(int times = 1);
    void Stop(int msToStop);
    void Open(std::string file);
    bool IsOpen();

    void Update(float dt);
    void Render();
    bool Is(std::string type);

  private:
    Mix_Chunk* chunk;
    int channel;
};

#endif
