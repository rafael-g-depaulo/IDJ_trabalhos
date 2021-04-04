#include "../include/Face.h"
#include "../include/Sound.h"

using namespace std;

Face::Face(GameObject& associated): Component(associated) {
  this->hitpoints = 30;
}

Face::~Face() {
}

void Face::Damage(int damage) {
  cout << "taking " << damage << " damage" << endl;

  this->hitpoints -= damage;
  if (this->hitpoints > 0) return;

  // check if it has a death sound. if so, play it
  auto sound = (Sound*) this->associated.GetComponent("Sound");
  if (sound != nullptr) {
    cout << "playing death sound" << endl;
    // TODO: fix sound play (not working)
    sound->Play(1);  
  }
  
  // remove object this is associated with
  this->associated.RequestDelete();
}

void Face::Update(float dt) { if (dt) {} }
void Face::Render() {}

bool Face::Is(string type) { return type == "Face"; }
