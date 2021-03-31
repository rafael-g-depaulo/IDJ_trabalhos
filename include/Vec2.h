#ifndef vec2_h
#define vec2_h

#include <iostream>

class Vec2 {
  public:
    Vec2(float x = 0.0, float y = 0.0);

    float x;
    float y;

    Vec2 operator+(const Vec2& vec);

    void print(const char* name = nullptr);
};

#endif
