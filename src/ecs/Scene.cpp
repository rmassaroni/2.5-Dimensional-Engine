#include "Scene.h"
#include "graphics/Renderer.h"
#include "graphics/Camera.h"
#include "world/Tilemap.h"
#include <algorithm>

Tilemap* gTilemap = nullptr;

void Scene::init(SDL_Renderer* renderer) {
    Renderer::set(renderer);

    // ===== PLACEHOLDER ASSETS =====
    // Replace these with YOUR files
    Sprite* tileset = new Sprite("assets/tileset.png");
    Sprite* playerSprite = new Sprite("assets/player.png");
    Sprite* npcSprite = new Sprite("assets/npc.png");

    playerSprite->setAnimation(32, 32, 4); // adjust for your Piskel export

    gTilemap = new Tilemap(25, 18, tileset);

    // Simple test map
    for (int y = 0; y < 18; y++) {
        for (int x = 0; x < 25; x++) {
            if (x == 0 || y == 0 || x == 24 || y == 17)
                gTilemap->setTile(x, y, 1, true);
            else
                gTilemap->setTile(x, y, 0, false);
        }
    }

    player = new Entity(100, 100, playerSprite);
    player->isPlayer = true;

    entities.push_back(player);

    // NPC
    entities.push_back(new Entity(200, 200, npcSprite));
}

void Scene::update() {
    for (auto e : entities)
        e->update();

    Camera::follow(player->x, player->y);
}

void Scene::render() {
    gTilemap->render();

    std::sort(entities.begin(), entities.end(),
        [](Entity* a, Entity* b) {
            return a->y < b->y;
        });

    for (auto e : entities)
        e->render();
}
