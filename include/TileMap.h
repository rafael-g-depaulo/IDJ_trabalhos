#ifndef tilemap_h
#define tilemap_h

#include <iostream>
#include <vector>

#include "./Component.h"
#include "./TileSet.h"

using namespace std;

class TileMap : Component {
  public:
    TileMap(GameObject& associatedObj, string file, TileSet* tileSet);
    
    // Component stuff
    void Update(float dt);
    void Render();
    bool Is(string type);

    void Load(string file);
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z = 0);
    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

    int GetWidth();
    int GetHeight();
    int GetDepth();

  private:
    vector<int> tileMatrix;
    TileSet* tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;
};

#endif
