#include "../include/TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, string file): tileSet(*(new GameObject()), file) {
  this->TileWidth = tileWidth;
  this->TileHeight = tileHeight;
  this->columns = this->tileSet.GetWidth() / this->TileWidth;
  this->rows = this->tileSet.GetHeight() / this->TileHeight;
}

void TileSet::RenderTile(unsigned int index, float x, float y) {

  // if index is 0, don't render anything
  if (index == 0) return;

  // this change is necessary because the tileMap given starts at 1, but tileIndexes start at 0
  unsigned int tileIndex = index - 1;

  // check if index is valid
  unsigned int maxIndex = this->columns * this->rows;
  if (tileIndex >= maxIndex) {
    cout << "tried to render TileSet tile, but given index (" << tileIndex << ") was out of bounds (max: " << maxIndex << ")" << endl;
    exit(0);
  }

  int tileX = tileIndex % this->columns;
  int tileY = tileIndex / this->columns;
  this->tileSet.SetClip(tileX * this->TileWidth, tileY * this->TileWidth, this->TileWidth, this->TileHeight);

  this->tileSet.Render((int) x, (int) y, this->GetTileWidth(), this->GetTileHeight());
}

int TileSet::GetTileHeight() { return this->TileHeight; }
int TileSet::GetTileWidth() { return this->TileWidth; }
