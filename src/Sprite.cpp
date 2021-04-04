#include "../include/Sprite.h"
#include "../include/Game.h"

using namespace std;

Sprite::Sprite(GameObject& associated): Component(associated) {
  this->texture = nullptr;
}

Sprite::Sprite(GameObject& associated, string file): Sprite(associated) {
  this->Open(file);
}

void Sprite::Open(string file) {
  // remove previous texture, if already had a file loaded
  if (this->texture != nullptr) {
    SDL_DestroyTexture(this->texture);
  }

  // load file
  // this
  SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
  this->texture = IMG_LoadTexture(renderer, file.c_str());

  // if file failed to load, crash gracefully (log and explode)
  if (this->texture == nullptr) {
    cout << "Error loading file into sprite: " << SDL_GetError() << endl;
    exit(0);
  }
  
  // get texture's dimensions into this->width and this->height
  int queryTextureErr = SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
  if (queryTextureErr == -1) {
    cout << "Error trying to get sprite texture's dimentions: " << SDL_GetError() << endl;
    exit(0);
  }

  // set clip
  this->SetClip(0, 0, this->width, this->height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
  this->clipRect.x = x;
  this->clipRect.y = y;
  this->clipRect.w = w;
  this->clipRect.h = h;
}

void Sprite::Render(int x, int y) {
  SDL_Renderer* renderer = Game::GetInstance().GetRenderer();

  // create rectangle for the sprite's size/location in the game window
  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  dst.w = this->GetWidth();
  dst.h = this->GetHeight();
  
  SDL_RenderCopy(renderer, this->texture, &this->clipRect, &dst);
}

int Sprite::GetHeight() { return this->clipRect.h; }
int Sprite::GetWidth()  { return this->clipRect.w; }

bool Sprite::IsOpen() {
  return texture != nullptr;
}

Sprite::~Sprite() {
  if (this->texture != nullptr) {
    SDL_DestroyTexture(this->texture);
  }
}
