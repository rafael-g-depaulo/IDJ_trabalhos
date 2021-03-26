#include "../include/Rect.h"

Rect::Rect() {
  this->x = 0;
  this->y = 0;
  this->h = 0;
  this->w = 0;
}

Rect::Rect(float x = 0, float y = 0, float w = 0, float h = 0) {
  this->x = x;
  this->y = y;
  this->h = h;
  this->w = w;
}