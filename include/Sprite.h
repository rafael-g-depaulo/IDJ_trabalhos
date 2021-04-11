#ifndef sprite_h
#define sprite_h

#include <iostream>
#include "SDL2/SDL_image.h" 

#include "./Component.h"

using namespace std;

class Sprite : Component {
  public:
    Sprite(GameObject& associated);
    Sprite(GameObject& associated, string file);
    ~Sprite();

    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    
    int GetWidth();
    int GetHeight();
    bool IsOpen();

    void Update(float dt);
    void Render();
    bool Is(std::string type);

  private:
    SDL_Texture* texture;
    SDL_Rect clipRect;
    int width;
    int height;
};

#endif
