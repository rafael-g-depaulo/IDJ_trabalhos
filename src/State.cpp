#include "../include/State.h"

#include "../include/TileMap.h"
#include "../include/Sound.h"
#include "../include/Face.h"

State::State(): music("./assets/audio/music.mp3") {
  this->quitRequested = false;
  this->music.Play(-1);
  this->LoadAssets();
}

State::~State() {
  this->objectArray.clear();
}

void State::LoadAssets() {
  // initialize background
  auto bgGO = new GameObject();
  this->bg = new Sprite(*bgGO, "./assets/img/ocean.jpg");
  bgGO->AddComponent((Component*) this->bg);
  this->objectArray.emplace_back((unique_ptr<GameObject>) bgGO);

  // initialize TileMap
  auto tmGO = new GameObject();
  tmGO->AddComponent((Component*) new TileMap(*tmGO, string("./assets/map/tileMap.txt"), new TileSet(64, 64, "./assets/img/tileset.png")));
  this->objectArray.emplace_back((unique_ptr<GameObject>) tmGO);
  // TODO: a especificação mandou desalocar o TileSet na hora certa. lembre de dar uma olhada nisso depois quando vc entender o que está acontecendo aqui
}

void State::Update(float dt) {
  // process input
  Input();

  // update all game objects
  for (auto i = this->objectArray.begin(); i != this->objectArray.end(); i++) {
    auto go = i->get();
    go->Update(dt);
  }

  // remove all dead game objects
  for (auto i = this->objectArray.begin(); i != this->objectArray.end(); i++) {
    auto object = i->get();
    if (object->IsDead()) {
      this->objectArray.erase(i);
      i--;
    }
  }

  // if user pressed the close button or alt+F4
  bool userWantsOff = SDL_QuitRequested();
  if (userWantsOff) {
    this->quitRequested = true;
    return;
  }  
}

void State::Input() {
  // get mouse position
  int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	SDL_Event event;
  while (SDL_PollEvent(&event)) {

    // if event is a quit-type, quit
    if (event.type == SDL_QUIT) this->quitRequested = true;

    // if clicked
    else if (event.type == SDL_MOUSEBUTTONDOWN) {
      // traverse vector backwards, looking if user clicked on a face
      for (auto i = this->objectArray.rbegin(); i != this->objectArray.rend(); i++) {
        auto go = i->get();
        // if there is a face, smack it
        if (go->box.contains(mouseX, mouseY)) {
          auto face = (Face*) go->GetComponent("Face");
          if (face != nullptr) {
            face->Damage(rand() % 10 + 10);
            break;
          }
        }
      }
    }

    if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				this->quitRequested = true;
			} else {
				// Vec2 objPos = Vec2( 200, 0 ).GetRotated( (-PI + PI*(rand() % 1001)/500.0) ) + Vec2( mouseX, mouseY );
				AddObject(mouseX, mouseY);
			}
		}

  }
}

void State::AddObject(int mouseX, int mouseY) {
  auto go = new GameObject();

  cout << "adding object at (" << mouseX << ", " << mouseY << ")" << endl;

  // create sprite and update go box
  auto penguinSprite = new Sprite(*go, "./assets/img/penguinface.png");
  // auto penguinSprite = new Sprite(*go, "./assets/img/1.jpg");
  go->box.w = penguinSprite->GetWidth();
  go->box.h = penguinSprite->GetHeight();
  go->box.x = mouseX - (go->box.w / 2);
  go->box.y = mouseY - (go->box.h / 2);

  // create sound
  auto penguinSound = new Sound(*go, "./assets/audio/boom.wav");

  // create face
  auto penguinFace = new Face(*go);

  go->AddComponent((Component*) penguinSprite);
  go->AddComponent((Component*) penguinSound);
  go->AddComponent((Component*) penguinFace);
  
  this->objectArray.emplace_back((unique_ptr<GameObject>) go);
}

bool State::QuitRequested() {
  return this->quitRequested;
}

void State::Render() {
  // cout << "rendering State. Currently has " << this->objectArray.size() << " objects" << endl;
  for (auto i = this->objectArray.begin(); i != this->objectArray.end(); i++) {
    auto object = i->get();
    object->Render();
  }
}
