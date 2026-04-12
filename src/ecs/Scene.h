#pragma once
#include <vector>
#include "Entity.h"

class Scene {
public:
    void init(SDL_Renderer* renderer);
    void update();
    void render();

private:
    std::vector<Entity*> entities;
    Entity* player;
};
