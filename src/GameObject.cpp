#include "../include/GameObject.h"
#include <algorithm>

using namespace std;

GameObject::GameObject() {
  this->isDead = false;
}

GameObject::~GameObject() {
  // delete all items from vector
  for (const auto component : this->components)
    delete component;

  this->components.clear();
}

void GameObject::Update(float dt) {
  for (const auto component : this->components)
    component->Update(dt);
}

void GameObject::Render() {
  // cout << "Rendering Game Object with " << this->components.size() << " components" << endl;
  for (const auto component : this->components)
    component->Render();
}

bool GameObject::IsDead() { return this->isDead; }
void GameObject::RequestDelete() { this->isDead = true; }

void GameObject::AddComponent(Component* cpt) {
  this->components.push_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
  // get positions
  auto begin = this->components.begin();
  auto end = this->components.end();
  
  // search for component
  auto cptPosition = find(begin, end, cpt);

  // delete if it exists
  if (cptPosition != end) {
    this->components.erase(cptPosition);
  }
}

Component* GameObject::GetComponent(std::string type) {
  for (const auto component : this->components)
  if (component->Is(type)) return component;

  return nullptr;
}
