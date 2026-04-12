#include "Tilemap.h"
#include "graphics/Renderer.h"
#include "graphics/Camera.h"

Tilemap::Tilemap(int w, int h, Sprite* tileset)
    : width(w), height(h), tileset(tileset)
{
    tiles.resize(w * h);
    wallTiles.resize(w * h);
}

// void Tilemap::setTile(int x, int y, int id, bool solid) {
//     tiles[y * width + x] = Tile(id, solid);
// }
void Tilemap::setTile(int x, int y, int id, bool solid, int height) {
    tiles[y * width + x] = Tile(id, solid, height);
}

bool Tilemap::isSolid(int x, int y) {
    if (x < 0 || y < 0 || x >= width || y >= height)
        return true;
    return tiles[y * width + x].solid;
}

void Tilemap::setWall(int x, int y, int id, int height) {
    wallTiles[y * width + x] = Tile(id, true, height);
}

void Tilemap::render() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            Tile& t = tiles[y * width + x];

            SDL_Rect src = { t.id * tileSize, 0, tileSize, tileSize };

            // SDL_Rect dst = {
            //     x * tileSize - Camera::x,
            //     y * tileSize - Camera::y,
            //     tileSize, tileSize
            // };
            int screenX = x * tileSize - Camera::x;
            int screenY = y * tileSize - Camera::y;

            // Apply vertical height offset (THIS IS THE MAGIC)
            screenY -= t.height * tileSize;

            SDL_Rect dst = {
                screenX,
                screenY,
                tileSize,
                tileSize
            };

            SDL_RenderCopy(Renderer::sdlRenderer,
                           tileset->texture,
                           &src, &dst);

            Tile& wall = wallTiles[y * width + x];

            if (wall.id != 0) {
                int wx = x * tileSize - Camera::x;
                int wy = y * tileSize - Camera::y - wall.height * tileSize;

                SDL_Rect src = { wall.id * tileSize, 0, tileSize, tileSize };
                SDL_Rect dst = { wx, wy, tileSize, tileSize };

                SDL_RenderCopy(Renderer::sdlRenderer,
                               tileset->texture, &src, &dst);
            }
        }
    }
}
