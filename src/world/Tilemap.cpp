#include "Tilemap.h"
#include "graphics/Renderer.h"
#include "graphics/Camera.h"
#include <SDL2/SDL.h>

Tilemap::Tilemap(int w, int h, Sprite* tileset)
    : width(w), height(h), tileset(tileset)
{
    tiles.resize(w * h);
}

void Tilemap::setTile(int x, int y, int id, bool solid, int tileHeight) {
    if (x < 0 || y < 0 || x >= width || y >= this->height) {
        return;
    }

    tiles[y * width + x] = Tile(id, solid, tileHeight);
}

bool Tilemap::isSolid(int x, int y) {
    if (x < 0 || y < 0 || x >= width || y >= height) {
        return true;
    }

    return tiles[y * width + x].solid;
}

bool Tilemap::hasSolidNeighbor(int x, int y) {
    if (x < 0 || y < 0 || x >= width || y >= height)
        return false;

    return tiles[y * width + x].height > 0;
}

void Tilemap::drawTile(int tileId, int screenX, int screenY) {
    if (!tileset || !tileset->texture) {
        return;
    }

    SDL_Rect src = {
        tileId * tileSize,
        0,
        tileSize,
        tileSize
    };

    SDL_Rect dst = {
        screenX,
        screenY,
        tileSize,
        tileSize
    };

    SDL_RenderCopy(Renderer::sdlRenderer, tileset->texture, &src, &dst);
}
void Tilemap::drawTileScaled(int tileId, int screenX, int screenY, int drawWidth, int drawHeight) {
    if (!tileset || !tileset->texture) {
        return;
    }

    SDL_Rect src = {
        tileId * tileSize,
        0,
        tileSize,
        tileSize
    };

    SDL_Rect dst = {
        screenX,
        screenY,
        drawWidth,
        drawHeight
    };

    SDL_RenderCopy(Renderer::sdlRenderer, tileset->texture, &src, &dst);
}

void Tilemap::render(int playerX, int playerY) {
    if (!tileset || !tileset->texture) {
        return;
    }

    const int GROUND_TILE = 0;
    const int TOP_TILE    = 1;
    const int LEFT_WALL   = 2;
    const int RIGHT_WALL  = 3;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Tile& t = tiles[y * width + x];

            int baseScreenX = x * tileSize - Camera::x;
            int baseScreenY = y * tileSize - Camera::y;

            if (t.height <= 0) {
                drawTile(GROUND_TILE, baseScreenX, baseScreenY);
                continue;
            }

            bool playerIsRight = playerX > (x * tileSize);
            int dx = playerX - (x * tileSize);
            int absDx = dx < 0 ? -dx : dx;

            // int minWidth = 8;
            int minWidth = 4;
            int maxWidth = tileSize;

             // int wallWidth = maxWidth - (absDx / 8);
                        int wallWidth = maxWidth - (absDx / 6);
            if (wallWidth < minWidth) wallWidth = minWidth;
            if (wallWidth > maxWidth) wallWidth = maxWidth;

            bool hasLeft  = hasSolidNeighbor(x - 1, y);
            bool hasRight = hasSolidNeighbor(x + 1, y);
            bool hasFront = hasSolidNeighbor(x, y + 1); // below
            bool hasBack  = hasSolidNeighbor(x, y - 1); // above

            for (int level = 0; level < t.height; level++) {
                int faceY = baseScreenY - (level * tileSize);

                if (playerIsRight) {
                    // drawTile(RIGHT_WALL, baseScreenX, faceY);
                    // drawTileScaled(RIGHT_WALL, baseScreenX, faceY, wallWidth, tileSize);
                    if (!hasRight) {
                        drawTile(RIGHT_WALL, baseScreenX, faceY);
                    }
                } else {
                    // drawTile(LEFT_WALL, baseScreenX, faceY);
                    //  int shiftedX = baseScreenX + (tileSize - wallWidth);
                    // drawTileScaled(LEFT_WALL, shiftedX, faceY, wallWidth, tileSize);
                    if (!hasLeft) {
                        drawTile(LEFT_WALL, baseScreenX, faceY);
                    }
                }
            }

            int topY = baseScreenY - (t.height * tileSize);
            drawTile(TOP_TILE, baseScreenX, topY);
        }
    }
}
