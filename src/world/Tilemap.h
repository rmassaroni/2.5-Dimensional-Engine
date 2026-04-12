#pragma once
#include <vector>
#include "Tile.h"
#include "graphics/Sprite.h"

class Tilemap {
public:
    int width, height;
    int tileSize = 32;

    std::vector<Tile> tiles;
    Sprite* tileset;

    Tilemap(int w, int h, Sprite* tileset);

    void setTile(int x, int y, int id, bool solid);
    void render();
    bool isSolid(int x, int y);
};
