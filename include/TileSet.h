#ifndef tileset_h
#define tileset_h

#include <iostream>

#include "./Sprite.h"

using namespace std;

class TileSet {
  public:
    TileSet(int tileWidth, int tileHeight, string file);

    int GetTileWidth();
    int GetTileHeight();
    
    void RenderTile(unsigned int index, float x, float y);
    
  private:
    Sprite tileSet;
    int TileWidth;
    int TileHeight;
    int rows;
    int columns;
};

#endif
