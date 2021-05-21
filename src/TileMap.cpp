#include <fstream>
#include <sstream>
#include <regex>

#include "../include/TileMap.h"

TileMap::TileMap(GameObject& associatedObj, string file, TileSet* tileSet): Component(associatedObj) {
  this->SetTileSet(tileSet);
  this->Load(file);
}

// TODO
void TileMap::Update(float dt) {}
// TODO
void TileMap::Render() {}

vector<int> getMapDimensions(string dimensionsStr) {
  vector<int> dims;
  regex dimensionsRegex("(\\d+),(\\d+),(\\d+),");
  smatch regexResults;
  
  // execute regex search
  if (!regex_search(dimensionsStr, regexResults, dimensionsRegex)) {
    cout << "TileMap file has bad sintax." << endl;
    exit(0);
  }

  // push into vector
  for (int i = 1; i < regexResults.size(); i++) {
    dims.push_back(stoi(regexResults[i]));
  }
  
  // return
  return dims;
}

void addLineContentToVector(string line, vector<int>& vec) {
  istringstream lineStream(line);
  string token;
  while (getline(lineStream, token, ',')) {
    cout << token << ", ";
    vec.push_back(atoi(token.c_str()));
  }
}

void TileMap::Load(string fileName) {
  ifstream file;
  file.open(fileName);

  if (!file.is_open()) {
    cout << "Error loading \"" << fileName << "\" text file..." << endl;
    exit(0);
  }

  string line;
  string fileContent;
  int lineCount = 0;
  while (getline(file, line)) {
    // if first line, get dimensions
    if (lineCount++ == 0) {
      auto matrixDimensions = getMapDimensions(line);
      cout << "tileMap width: " << matrixDimensions[0] << " height: " << matrixDimensions[1] << " depth: " << matrixDimensions[2] << endl;
      this->mapWidth = matrixDimensions[0];
      this->mapHeight = matrixDimensions[1];
      this->mapDepth = matrixDimensions[2];
    } else {
      addLineContentToVector(line, this->tileMatrix);
    }
  }
}


int& TileMap::At(int x, int y, int z) {
  int index = z * this->mapWidth * this->mapHeight + y * this->mapWidth + x;
  // TODO: add handling for x, y and z out of bounds
  return this->tileMatrix[index];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
  // iterate over X and Y axis
  for (int x = 0; x < this->mapWidth; x++)
  for (int y = 0; y < this->mapHeight; y++) {
    // calculate where in the window to render tile (take into account the given camera offset)
    int xPos = x * this->tileSet->GetTileWidth() + cameraX;
    int yPos = y * this->tileSet->GetTileHeight() + cameraY;
    // call tileSet to render the correct tile at that position
    this->tileSet->RenderTile(this->At(x, y, layer), xPos, yPos);
  }
}

bool TileMap::Is(string type) { return type == "TileMap"; }
void TileMap::SetTileSet(TileSet* tileSet) { this->tileSet = tileSet; }
int TileMap::GetWidth()  { return this->mapWidth;  }
int TileMap::GetHeight() { return this->mapHeight; }
int TileMap::GetDepth()  { return this->mapDepth;  }
