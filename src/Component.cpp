#include "../include/Component.h"

using namespace std;

Component::Component(GameObject& associatedObj): associated(associatedObj) {
}

// even though these are virtual i need to define basic versions of them for some reason
Component::~Component() {}
void Component::Update(float dt) { if (dt) {} }
void Component::Render() {}
bool Component::Is(string type) {
  if (type == "") return false;
  return false;
}
