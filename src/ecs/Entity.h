#pragma once
#include "graphics/Sprite.h"

class Entity {
public:
    int x, y;
    float speed = 200.0f;

    bool isPlayer = false;

    Sprite* sprite;

    Entity(int x, int y, Sprite* sprite);

    void update();
    void render();
};
