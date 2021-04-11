#include "../include/Face.h"
#include "../include/Sound.h"

using namespace std;

Face::Face(GameObject& associated): Component(associated) {
  this->hitpoints = 30;
  this->total_death_time = 1000;  // spend 1s dying before deleting object
  this->isDying = false;
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
    sound->Play(1);  
  }
  
  // initiate death counter (i.e.: wait until death sound finishes before deleting object)
  this->isDying = true;

  // remove sprite
  auto sprite = this->associated.GetComponent("Sprite");
  this->associated.RemoveComponent(sprite);
}

void Face::Update(float dt) {
  // if this is dying, uptade death timer
  if (this->isDying) {
    this->death_time += dt;
  
    // if already time to die, do so and remove the object this is associated with
    if (this->death_time >= this->total_death_time)
      this->associated.RequestDelete();
  }
}

void Face::Render() {}

bool Face::Is(string type) { return type == "Face"; }
