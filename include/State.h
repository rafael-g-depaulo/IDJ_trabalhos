#ifndef state_h
#define state_h

#include <memory>

#include "Sprite.h"
#include "Music.h"

using namespace std;

class State {
  public:
    State();
    ~State();

    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();

  private:
    Sprite* bg;
    Music music;
    bool quitRequested;
    vector<unique_ptr<GameObject>> objectArray;
};

#endif
