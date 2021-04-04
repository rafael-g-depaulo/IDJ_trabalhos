#ifndef rect_h
#define rect_h

#include "./Vec2.h"

class Rect {
  public:
    Rect();
    Rect(Vec2 pos, float w, float h);
    Rect(float x, float y, float w, float h);

    void print(const char* name = nullptr);
    
    bool contains(int x, int y);
    bool contains(float x, float y);
    bool contains(Vec2 point);

    float x;
    float y;
    float w;
    float h;
};

#endif
