#ifndef face_h
#define face_h

#include "./GameObject.h"
#include "./Component.h"

class Face : Component {
  public:
    Face(GameObject& associated);
    ~Face();

    void Update(float dt);
    void Render();
    bool Is(std::string type);

    void Damage(int damage);
  private:
    int hitpoints;
};

#endif
