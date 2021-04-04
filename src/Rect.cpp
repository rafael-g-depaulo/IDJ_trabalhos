#include "../include/Rect.h"

#include <iostream>

using namespace std;

Rect::Rect() {
  this->x = 0;
  this->y = 0;
  this->h = 0;
  this->w = 0;
}

Rect::Rect(Vec2 pos, float w, float h) {
  this->x = pos.x;
  this->y = pos.y;
  this->h = h;
  this->w = w;
}

Rect::Rect(float x = 0, float y = 0, float w = 0, float h = 0) {
  this->x = x;
  this->y = y;
  this->h = h;
  this->w = w;
}

void Rect::print(const char* name) {
  if (name != nullptr) {
    cout << name << ": ";
  }
  cout << "top-right" << "(" << this->x << ", " << this->y << ")" <<
    "; bottom-left(" << this->x + this->w << ", " << this->y + this->h << ")" << endl;
}

bool Rect::contains(int x, int y) { return this->contains((float) x, (float) y); }
bool Rect::contains(float x, float y) { return this->contains(Vec2(x, y)); }
bool Rect::contains(Vec2 point) {
  bool withinY = (point.y >= this->y) && (point.y <= this->y + this->h);
  bool withinX = (point.x >= this->x) && (point.x <= this->x + this->w);
  return withinX && withinY;
}
