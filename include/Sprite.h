#ifndef sprite_h
#define sprite_h

#include <iostream>
#include "SDL2/SDL_image.h" 

using namespace std;

class Sprite {
  public:
    Sprite();
    ~Sprite();
    Sprite(string file);

    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    int GetWidth();
    int GetHeight();
    bool IsOpen();

  private:
    SDL_Texture* texture;
    SDL_Rect clipRect;
    int width;
    int height;
};

#endif
