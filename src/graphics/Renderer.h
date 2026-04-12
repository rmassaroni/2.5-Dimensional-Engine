#pragma once
#include <SDL2/SDL.h>

class Renderer {
public:
    static SDL_Renderer* sdlRenderer;
    static void set(SDL_Renderer* r) { sdlRenderer = r; }
};
