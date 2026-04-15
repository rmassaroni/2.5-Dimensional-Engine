#include "Scene.h"
#include "graphics/Renderer.h"
#include "graphics/Camera.h"
#include "world/Tilemap.h"
#include <algorithm>

Tilemap* gTilemap = nullptr;

void Scene::init(SDL_Renderer* renderer) {
    Renderer::set(renderer);

    Sprite* tileset = new Sprite("assets/tileset.png");
    Sprite* playerSprite = new Sprite("assets/player.png");
    Sprite* npcSprite = new Sprite("assets/npc.png");

    playerSprite->setAnimation(32, 32, 4);

    gTilemap = new Tilemap(40, 30, tileset);

    // Flat ground everywhere
    for (int y = 0; y < 30; y++) {
        for (int x = 0; x < 40; x++) {
            gTilemap->setTile(x, y, 0, false, 0);
        }
    }

    // Big raised block in center
    for (int y = 10; y <= 14; y++) {
        for (int x = 12; x <= 18; x++) {
            gTilemap->setTile(x, y, 1, true, 3);
        }
    }

    // Player starts left of structure
    player = new Entity(300, 360, playerSprite);
    player->isPlayer = true;
    entities.push_back(player);

    // NPC to the right
    Entity* npc = new Entity(650, 360, npcSprite);
    entities.push_back(npc);
}

void Scene::update() {
    for (auto e : entities)
        e->update();

    Camera::follow(player->x, player->y);
}

void Scene::render() {
    gTilemap->render(player->x, player->y);

    std::sort(entities.begin(), entities.end(),
        [](Entity* a, Entity* b) {
            return (a->y + a->z) < (b->y + b->z);
        });

    for (auto e : entities)
        e->render();
}



// #include "Scene.h"
// #include "graphics/Renderer.h"
// #include "graphics/Camera.h"
// #include "world/Tilemap.h"
// #include <algorithm>
//
// Tilemap* gTilemap = nullptr;
//
// void Scene::init(SDL_Renderer* renderer) {
//     Renderer::set(renderer);
//
//     // ===== PLACEHOLDER ASSETS =====
//     // Make sure these files exist in /build/assets/
//     Sprite* tileset = new Sprite("assets/tileset.png");
//     Sprite* playerSprite = new Sprite("assets/player.png");
//     Sprite* npcSprite = new Sprite("assets/npc.png");
//
//     // Adjust depending on your Piskel sprite sheet
//     playerSprite->setAnimation(32, 32, 4);
//
//     gTilemap = new Tilemap(25, 18, tileset);
//
//     // ===== BASE GROUND =====
//     for (int y = 0; y < 18; y++) {
//         for (int x = 0; x < 25; x++) {
//             gTilemap->setTile(x, y, 0, false, 0); // flat ground
//         }
//     }
//
//     // ===== BORDER WALLS (height = 1) =====
//     for (int x = 0; x < 25; x++) {
//         gTilemap->setTile(x, 0, 1, true, 1);
//         gTilemap->setTile(x, 17, 1, true, 1);
//     }
//
//     for (int y = 0; y < 18; y++) {
//         gTilemap->setTile(0, y, 1, true, 1);
//         gTilemap->setTile(24, y, 1, true, 1);
//     }
//
//     // ===== RAISED PLATFORM TEST (THIS IS YOUR "WALL") =====
//     // This creates a 2x3 elevated structure with visible sides
//
//     for (int y = 5; y <= 6; y++) {
//         for (int x = 5; x <= 7; x++) {
//             gTilemap->setTile(x, y, 1, true, 2); // height = 2
//         }
//     }
//
//     // ===== PLAYER =====
//     player = new Entity(100, 100, playerSprite);
//     player->isPlayer = true;
//     entities.push_back(player);
//
//     // ===== NPC =====
//     Entity* npc = new Entity(200, 200, npcSprite);
//     entities.push_back(npc);
// }
//
// void Scene::update() {
//     for (auto e : entities)
//         e->update();
//
//     Camera::follow(player->x, player->y);
// }
//
// void Scene::render() {
//     // Draw world first
//     // gTilemap->render();
// gTilemap->render(player->x, player->y);
//
//     // Depth sort (important for 2.5D)
//     std::sort(entities.begin(), entities.end(),
//         [](Entity* a, Entity* b) {
//             return (a->y + a->z) < (b->y + b->z);
//         });
//
//     // Draw entities
//     for (auto e : entities)
//         e->render();
// }
// // #include "Scene.h"
// // #include "graphics/Renderer.h"
// // #include "graphics/Camera.h"
// // #include "world/Tilemap.h"
// // #include <algorithm>
// //
// // Tilemap* gTilemap = nullptr;
// //
// // void Scene::init(SDL_Renderer* renderer) {
// //     Renderer::set(renderer);
// //
// //     // ===== PLACEHOLDER ASSETS =====
// //     // Replace these with YOUR files
// //     Sprite* tileset = new Sprite("assets/tileset.png");
// //     Sprite* playerSprite = new Sprite("assets/player.png");
// //     Sprite* npcSprite = new Sprite("assets/npc.png");
// //
// //     playerSprite->setAnimation(32, 32, 4); // adjust for your Piskel export
// //
// //     gTilemap = new Tilemap(25, 18, tileset);
// //
// //     // Simple test map
// //     for (int y = 0; y < 18; y++) {
// //         for (int x = 0; x < 25; x++) {
// //             if (x == 0 || y == 0 || x == 24 || y == 17)
// //                 // gTilemap->setTile(x, y, 1, true);
// //                 gTilemap->setTile(x, y, 1, true, 1); // height = 1 → wall
// //             else
// //                 gTilemap->setTile(x, y, 0, false);
// //         }
// //     }
// //
// //     // ===== TEST WALLS (ADD HERE) =====
// //     // gTilemap->setWall(5, 5, 2, 2);
// //     // gTilemap->setWall(6, 5, 2, 2);
// //     // gTilemap->setWall(7, 5, 2, 2);
// //     gTilemap->setWall(5, 5, 1, 3);
// //     gTilemap->setWall(6, 5, 1, 3);
// //     gTilemap->setWall(7, 5, 1, 3);
// //
// //     player = new Entity(100, 100, playerSprite);
// //     player->isPlayer = true;
// //
// //     entities.push_back(player);
// //
// //     // NPC
// //     entities.push_back(new Entity(200, 200, npcSprite));
// // }
// //
// // void Scene::update() {
// //     for (auto e : entities)
// //         e->update();
// //
// //     Camera::follow(player->x, player->y);
// // }
// //
// // void Scene::render() {
// //     gTilemap->render();
// //
// //     std::sort(entities.begin(), entities.end(),
// //         [](Entity* a, Entity* b) {
// //             // return a->y < b->y;
// //               return (a->y + a->z) < (b->y + b->z);
// //         });
// //
// //     for (auto e : entities)
// //         e->render();
// // }
