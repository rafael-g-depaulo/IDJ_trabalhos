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

    void Input();
    void AddObject(int mouseX, int mouseY);

  private:
    Sprite* bg;
    Music music;
    bool quitRequested;
    vector<unique_ptr<GameObject>> objectArray;
};

#endif
