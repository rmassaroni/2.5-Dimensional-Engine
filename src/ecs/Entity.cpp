#include "Entity.h"
#include "core/Input.h"
#include "core/Time.h"
#include "world/Tilemap.h"
#include <SDL2/SDL.h>
#include <cmath>

extern Tilemap* gTilemap;

Entity::Entity(int x, int y, Sprite* sprite)
    : x(x), y(y), sprite(sprite) {}


void Entity::update() {
    if (!isPlayer) return;

    float dx = 0;
    float dy = 0;

    if (Input::keyDown(SDL_SCANCODE_W)) dy -= 1;
    if (Input::keyDown(SDL_SCANCODE_S)) dy += 1;
    if (Input::keyDown(SDL_SCANCODE_A)) dx -= 1;
    if (Input::keyDown(SDL_SCANCODE_D)) dx += 1;

    if (Input::keyDown(SDL_SCANCODE_UP)) dy -= 1;
if (Input::keyDown(SDL_SCANCODE_DOWN)) dy += 1;
if (Input::keyDown(SDL_SCANCODE_LEFT)) dx -= 1;
if (Input::keyDown(SDL_SCANCODE_RIGHT)) dx += 1;

    // Normalize diagonal movement
    float length = sqrt(dx * dx + dy * dy);
    if (length > 0) {
        dx /= length;
        dy /= length;
    }

    float newX = x + dx * speed * Time::deltaTime;
    float newY = y + dy * speed * Time::deltaTime;

    // Collision (same as before)
    if (!gTilemap->isSolid(newX / 32, y / 32))
        x = newX;

    if (!gTilemap->isSolid(x / 32, newY / 32))
        y = newY;
}

void Entity::render() {
    if (sprite)
        sprite->draw(x, y);
}
// #include "Entity.h"
// #include "core/Input.h"
// #include "core/Time.h"
// #include "world/Tilemap.h"
// #include <SDL2/SDL.h>
//
// extern Tilemap* gTilemap;
//
// Entity::Entity(int x, int y, Sprite* sprite)
//     : x(x), y(y), sprite(sprite) {}
//
// void Entity::update() {
//     if (!isPlayer) return;
//
//     float dx = 0, dy = 0;
//
//     if (Input::keyDown(SDL_SCANCODE_W)) dy -= 1;
//     if (Input::keyDown(SDL_SCANCODE_S)) dy += 1;
//     if (Input::keyDown(SDL_SCANCODE_A)) dx -= 1;
//     if (Input::keyDown(SDL_SCANCODE_D)) dx += 1;
//
//     float newX = x + dx * speed * Time::deltaTime;
//     float newY = y + dy * speed * Time::deltaTime;
//
//     if (!gTilemap->isSolid(newX / 32, y / 32))
//         x = newX;
//
//     if (!gTilemap->isSolid(x / 32, newY / 32))
//         y = newY;
// }
//
// void Entity::render() {
//     sprite->draw(x, y);
// }
