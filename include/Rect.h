#ifndef rect_h
#define rect_h

#include "./Vec2.h"

class Rect {
  public:
    Rect();
    Rect(Vec2 pos, float w, float h);
    Rect(float x, float y, float w, float h);

    float x;
    float y;
    float w;
    float h;
};

#endif
