#ifndef component_h
#define component_h

#include <iostream>
#include "./GameObject.h"

class Component {
  public:
    Component(const GameObject& associatedObj);
    ~Component();

    virtual void Update(float dt);
    virtual void Render();
    virtual bool Is(std::string type);

  private:
    GameObject& associated;
};

#endif
