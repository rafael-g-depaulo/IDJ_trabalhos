#ifndef component_h
#define component_h

#include <iostream>

class Component;

#include "./GameObject.h"

class Component {
  public:
    Component(GameObject& associatedObj);
    virtual ~Component();

    virtual void Update(float dt);
    virtual void Render();
    virtual bool Is(std::string type);

  protected:
    GameObject& associated;
};

#endif
