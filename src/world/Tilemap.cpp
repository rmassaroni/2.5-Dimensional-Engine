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
    // Use this->height so we compare against map height, not tile elevation
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

void Tilemap::render(int playerX, int playerY) {
    if (!tileset || !tileset->texture) {
        return;
    }

    // tileset layout:
    // 0 = ground
    // 1 = top surface
    // 2 = left wall face
    // 3 = right wall face
    const int GROUND_TILE = 0;
    const int TOP_TILE    = 1;
    const int LEFT_WALL   = 2;
    const int RIGHT_WALL  = 3;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Tile& t = tiles[y * width + x];

            int baseScreenX = x * tileSize - Camera::x;
            int baseScreenY = y * tileSize - Camera::y;

            // Flat ground
            if (t.height <= 0) {
                drawTile(GROUND_TILE, baseScreenX, baseScreenY);
                continue;
            }

            // Decide which wall face to show based on player position
            bool playerIsRight = playerX > (x * tileSize);

            // Draw vertical side faces
            for (int level = 0; level < t.height; level++) {
                int faceY = baseScreenY - (level * tileSize);

                if (playerIsRight) {
                    drawTile(RIGHT_WALL, baseScreenX, faceY);
                } else {
                    drawTile(LEFT_WALL, baseScreenX, faceY);
                }
            }

            // Draw the top tile above the wall stack
            int topY = baseScreenY - (t.height * tileSize);
            drawTile(TOP_TILE, baseScreenX, topY);
        }
    }
}
// #include "Tilemap.h"
// #include "graphics/Renderer.h"
// #include "graphics/Camera.h"
// #include <SDL2/SDL.h>
//
// Tilemap::Tilemap(int w, int h, Sprite* tileset)
//     : width(w), height(h), tileset(tileset)
// {
//     tiles.resize(w * h);
// }
//
// void Tilemap::setTile(int x, int y, int id, bool solid, int height) {
//     if (x < 0 || y < 0 || x >= width || y >= height) return;
//     tiles[y * width + x] = Tile(id, solid, height);
// }
//
// bool Tilemap::isSolid(int x, int y) {
//     if (x < 0 || y < 0 || x >= width || y >= height)
//         return true;
//
//     return tiles[y * width + x].solid;
// }
//
// void Tilemap::drawTile(int tileId, int screenX, int screenY) {
//     if (!tileset || !tileset->texture) return;
//
//     SDL_Rect src = {
//         tileId * tileSize,
//         0,
//         tileSize,
//         tileSize
//     };
//
//     SDL_Rect dst = {
//         screenX,
//         screenY,
//         tileSize,
//         tileSize
//     };
//
//     SDL_RenderCopy(Renderer::sdlRenderer, tileset->texture, &src, &dst);
// }
//
// void Tilemap::render(int playerX, int playerY) {
//     if (!tileset || !tileset->texture) return;
//
//     // tileset layout:
//     // 0 = ground
//     // 1 = top surface
//     // 2 = left wall face
//     // 3 = right wall face
//     const int GROUND_TILE = 0;
//     const int TOP_TILE    = 1;
//     const int LEFT_WALL   = 2;
//     const int RIGHT_WALL  = 3;
//
//     for (int y = 0; y < height; y++) {
//         for (int x = 0; x < width; x++) {
//             Tile& t = tiles[y * width + x];
//
//             int baseScreenX = x * tileSize - Camera::x;
//             int baseScreenY = y * tileSize - Camera::y;
//
//             if (t.height <= 0) {
//                 drawTile(GROUND_TILE, baseScreenX, baseScreenY);
//                 continue;
//             }
//
//             bool playerIsRight = playerX > x * tileSize;
//
//             for (int level = 0; level < t.height; level++) {
//                 int faceY = baseScreenY - (level * tileSize);
//
//                 if (playerIsRight) {
//                     drawTile(RIGHT_WALL, baseScreenX, faceY);
//                 } else {
//                     drawTile(LEFT_WALL, baseScreenX, faceY);
//                 }
//             }
//
//             int topY = baseScreenY - (t.height * tileSize);
//             drawTile(TOP_TILE, baseScreenX, topY);
//         }
//     }
// }
// // #include "Tilemap.h"
// // #include "graphics/Renderer.h"
// // #include "graphics/Camera.h"
// // #include <SDL2/SDL.h>
// //
// // const int GROUND_TILE = 0;
// // const int TOP_TILE    = 1;
// // const int LEFT_WALL   = 2;
// // const int RIGHT_WALL  = 2;
// //
// // Tilemap::Tilemap(int w, int h, Sprite* tileset)
// //     : width(w), height(h), tileset(tileset)
// // {
// //     tiles.resize(w * h);
// //     // wallTiles.resize(w * h);
// // }
// //
// // // void Tilemap::setTile(int x, int y, int id, bool solid) {
// // //     tiles[y * width + x] = Tile(id, solid);
// // // }
// // void Tilemap::setTile(int x, int y, int id, bool solid, int height) {
// //     if (x < 0 || y < 0 || x >= width || y >= height) return;
// //     tiles[y * width + x] = Tile(id, solid, height);
// // }
// //
// // bool Tilemap::isSolid(int x, int y) {
// //     if (x < 0 || y < 0 || x >= width || y >= height)
// //         return true;
// //     return tiles[y * width + x].solid;
// // }
// //
// // // void Tilemap::setWall(int x, int y, int id, int height) {
// // //     wallTiles[y * width + x] = Tile(id, true, height);
// // // }
// // void Tilemap::drawTile(int tileId, int screenX, int screenY) {
// //     if (!tileset || !tileset->texture) return;
// //
// //     SDL_Rect src = {
// //         tileId * tileSize,
// //         0,
// //         tileSize,
// //         tileSize
// //     };
// //
// //     SDL_Rect dst = {
// //         screenX,
// //         screenY,
// //         tileSize,
// //         tileSize
// //     };
// //
// //     SDL_RenderCopy(Renderer::sdlRenderer, tileset->texture, &src, &dst);
// // }
// // // void Tilemap::render() {
// // //     for (int y = 0; y < height; y++) {
// // //         for (int x = 0; x < width; x++) {
// // //
// // //             Tile& t = tiles[y * width + x];
// // //
// // //             SDL_Rect src = { t.id * tileSize, 0, tileSize, tileSize };
// // //
// // //             // SDL_Rect dst = {
// // //             //     x * tileSize - Camera::x,
// // //             //     y * tileSize - Camera::y,
// // //             //     tileSize, tileSize
// // //             // };
// // //             int screenX = x * tileSize - Camera::x;
// // //             int screenY = y * tileSize - Camera::y;
// // //
// // //             // Apply vertical height offset (THIS IS THE MAGIC)
// // //             screenY -= t.height * tileSize;
// // //
// // //             SDL_Rect dst = {
// // //                 screenX,
// // //                 screenY,
// // //                 tileSize,
// // //                 tileSize
// // //             };
// // //
// // //             SDL_RenderCopy(Renderer::sdlRenderer,
// // //                            tileset->texture,
// // //                            &src, &dst);
// // //
// // //             Tile& wall = wallTiles[y * width + x];
// // //
// // //             if (wall.id != 0) {
// // //                 // int wx = x * tileSize - Camera::x;
// // //                 // int wy = y * tileSize - Camera::y - wall.height * tileSize;
// // //                 //
// // //                 // SDL_Rect src = { wall.id * tileSize, 0, tileSize, tileSize };
// // //                 // SDL_Rect dst = { wx, wy, tileSize, tileSize };
// // //                 //
// // //                 // SDL_RenderCopy(Renderer::sdlRenderer,
// // //                 //                tileset->texture, &src, &dst);
// // //                 SDL_SetRenderDrawColor(Renderer::sdlRenderer, 255, 0, 0, 255);
// // //
// // //                 SDL_Rect debugRect = {
// // //                     x * tileSize - Camera::x,
// // //                     y * tileSize - Camera::y - 100, // push it up so you SEE it
// // //                     tileSize,
// // //                     tileSize
// // //                 };
// // //
// // //     SDL_RenderFillRect(Renderer::sdlRenderer, &debugRect);
// // //             }
// // //         }
// // //     }
// // // }
// //
// // // void Tilemap::render() {
// // void Tilemap::render(int playerX, int playerY) {
// //     if (!tileset || !tileset->texture) return;
// //
// //     // Tileset assumptions:
// //     // 0 = ground top
// //     // 1 = raised top / cliff top / platform top
// //     // 2 = wall side face
// //     //
// //     // You can change these indices later to match your tileset.
// //     const int defaultGroundTile = 0;
// //     const int defaultRaisedTopTile = 1;
// //     const int defaultWallSideTile = 2;
// //
// //     for (int y = 0; y < height; y++) {
// //         for (int x = 0; x < width; x++) {
// //             Tile& t = tiles[y * width + x];
// //
// //             int baseScreenX = x * tileSize - Camera::x;
// //             int baseScreenY = y * tileSize - Camera::y;
// //             // int baseScreenX = (x - y) * (tileSize / 2) - Camera::x;
// //             // int baseScreenY = (x + y) * (tileSize / 4) - Camera::y;
// //
// //             if (t.height <= 0) {
// //                 // Flat ground
// //                 int groundTileId = (t.id >= 0) ? t.id : defaultGroundTile;
// //                 drawTile(groundTileId, baseScreenX, baseScreenY);
// //                 continue;
// //             }
// //
// //             // Draw vertical wall faces from bottom upward
// //             // for (int level = 0; level < t.height; level++) {
// //             //     int faceY = baseScreenY - (level * tileSize);
// //             //     drawTile(defaultWallSideTile, baseScreenX, faceY);
// //             // }
// //             int dx = playerX - (x * tileSize);
// //             for (int level = 0; level < t.height; level++) {
// //                 int faceY = baseScreenY - (level * tileSize);
// //
// //                 if (dx > 0) {
// //                     drawTile(RIGHT_WALL, baseScreenX, faceY);
// //                 } else {
// //                     drawTile(LEFT_WALL, baseScreenX, faceY);
// //                 }
// //             }
// //
// //             int dy = playerY - (y * tileSize);
// //
// //             // Example: only draw right wall if player is to the right
// //             if (dx > 0) {
// //                 // draw right-facing wall
// //                 drawTile(RIGHT_WALL, baseScreenX, baseScreenY);
// //             }
// //
// //             // only draw left wall if player is to the left
// //             if (dx < 0) {
// //                 drawTile(LEFT_WALL, baseScreenX, baseScreenY);
// //             }
// //
// //             // Draw top tile above the side faces
// //             // int topY = baseScreenY - (t.height * tileSize);
// //             // int topY = baseScreenY - (t.height * (tileSize / 2));
// //
// //             int topY = baseScreenY - (t.height * tileSize);
// //             drawTile(TOP_TILE, baseScreenX, topY);
// //
// //             int topTileId = t.id;
// //             if (topTileId == 0) {
// //                 topTileId = defaultRaisedTopTile;
// //             }
// //
// //             drawTile(topTileId, baseScreenX, topY);
// //         }
// //     }
// // }
