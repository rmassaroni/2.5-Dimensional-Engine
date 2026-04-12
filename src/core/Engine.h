#pragma once
#include <SDL2/SDL.h>
#include "ecs/Scene.h"

class Engine {
public:
    bool init();
    void run();
    void clean();

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool running = false;

    Scene scene;

    void handleEvents();
    void update();
    void render();
};
