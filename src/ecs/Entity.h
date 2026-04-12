#pragma once
#include "graphics/Sprite.h"

class Entity {
public:
    int x, y;
    float speed = 200.0f;
    int z = 0; // height (for later use)

    bool isPlayer = false;

    Sprite* sprite;

    Entity(int x, int y, Sprite* sprite);

    void update();
    void render();
};
