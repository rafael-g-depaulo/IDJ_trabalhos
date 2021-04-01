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

Vec2 Vec2::operator-(const Vec2& vec) {
  Vec2* result = new Vec2();
  result->x = this->x - vec.x;
  result->y = this->y - vec.y;
  return *result;
}

Vec2 Vec2::operator*(float scale) {
  Vec2* result = new Vec2();
  result->x = this->x * scale;
  result->y = this->y * scale;
  return *result;
}

Vec2 Vec2::normalize() {
  auto mag = this->magnitude();
  auto result = new Vec2(this->x / mag, this->y / mag);
  return *result;
}

float Vec2::magnitude() {
  return sqrtf((this->x * this->x) + (this->y * this->y));
}

float Vec2::distanceTo(const Vec2& vec) {
  return (*this - vec).magnitude();
}
