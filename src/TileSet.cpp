#include "../include/TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, string file): tileSet(*(new GameObject()), file) {
  this->TileWidth = tileWidth;
  this->TileHeight = tileHeight;
  this->columns = this->tileSet.GetWidth() / this->TileWidth;
  this->rows = this->tileSet.GetHeight() / this->TileHeight;
}

void TileSet::RenderTile(unsigned int index, float x, float y) {
  // check if index is valid
  unsigned int maxIndex = this->columns * this->rows;
  if (index >= maxIndex) {
    cout << "tried to render TileSet tile, but given index (" << index << ") was out of bounds (max: " << maxIndex << ")" << endl;
    exit(0);
  }

  // i think this is wrong but i'm not sure why
  // TODO: fix maybe?
  this->tileSet.Render((int) x, (int) y, this->GetTileWidth(), this->GetTileHeight());
}

int TileSet::GetTileHeight() { return this->TileHeight; }
int TileSet::GetTileWidth() { return this->TileWidth; }
