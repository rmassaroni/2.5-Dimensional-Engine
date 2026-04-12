#include "Time.h"
#include <SDL2/SDL.h>

float Time::deltaTime = 0.0f;

void Time::update() {
    static Uint32 last = SDL_GetTicks();
    Uint32 now = SDL_GetTicks();

    deltaTime = (now - last) / 1000.0f;
    last = now;
}
