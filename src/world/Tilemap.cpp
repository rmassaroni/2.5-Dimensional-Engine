#include "Tilemap.h"
#include "graphics/Renderer.h"
#include "graphics/Camera.h"

Tilemap::Tilemap(int w, int h, Sprite* tileset)
    : width(w), height(h), tileset(tileset)
{
    tiles.resize(w * h);
}

void Tilemap::setTile(int x, int y, int id, bool solid) {
    tiles[y * width + x] = Tile(id, solid);
}

bool Tilemap::isSolid(int x, int y) {
    if (x < 0 || y < 0 || x >= width || y >= height)
        return true;
    return tiles[y * width + x].solid;
}

void Tilemap::render() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            Tile& t = tiles[y * width + x];

            SDL_Rect src = { t.id * tileSize, 0, tileSize, tileSize };

            SDL_Rect dst = {
                x * tileSize - Camera::x,
                y * tileSize - Camera::y,
                tileSize, tileSize
            };

            SDL_RenderCopy(Renderer::sdlRenderer,
                tileset->texture,
                &src, &dst);
        }
    }
}
