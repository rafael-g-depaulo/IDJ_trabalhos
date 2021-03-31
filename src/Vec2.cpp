#include "../include/Vec2.h"

using namespace std;

Vec2::Vec2(float x, float y) {
  this->x = x;
  this->y = y;
}

Vec2 Vec2::operator+(const Vec2& vec) {
  Vec2* result = new Vec2();
  result->x = this->x + vec.x;
  result->y = this->y + vec.y;
  return *result;
}


void Vec2::print(const char* name) {
  if (name != nullptr) {
    cout << name << ": " << "(" << this->x << ", " << this->y << ")" << endl;
  } else {
    cout << "x: " << this->x << " y: " << this->y << endl;
  }
}
