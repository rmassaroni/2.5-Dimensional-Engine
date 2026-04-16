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

    void setTile(int x, int y, int id, bool solid, int tileheight = 0);
    void render(int playerX, int playerY);
    bool isSolid(int x, int y);
private:
    void drawTile(int tileId, int screenX, int screenY);
    void drawTileScaled(int tileId, int screenX, int screenY, int drawWidth, int drawHeight);
    bool hasSolidNeighbor(int x, int y);
    int computeWallWidth(int playerX, int tileX);
};
