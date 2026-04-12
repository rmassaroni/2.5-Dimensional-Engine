#pragma once
#include <vector>
#include "Tile.h"
#include "graphics/Sprite.h"

class Tilemap {
public:
    int width, height;
    int tileSize = 32;

    std::vector<Tile> tiles;
    std::vector<Tile> wallTiles;

    Sprite* tileset;

    

    Tilemap(int w, int h, Sprite* tileset);

    // void setTile(int x, int y, int id, bool solid);
    void setTile(int x, int y, int id, bool solid, int height = 0);
    void setWall(int x, int y, int id, int height);

    void render();
    bool isSolid(int x, int y);
};
