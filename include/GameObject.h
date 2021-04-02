#ifndef game_object_h
#define game_object_h

#include <iostream>
#include <vector>

class GameObject;

#include "./Component.h"
#include "./Rect.h"

class GameObject {
  public:
    GameObject();
    ~GameObject();

    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(std::string type);

    Rect box;

  private:
    std::vector<Component*> components;
    bool isDead;
};

#endif
