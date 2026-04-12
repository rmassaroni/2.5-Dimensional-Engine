#pragma once
#include <SDL2/SDL.h>

class Input {
public:
    static void update();
    static bool keyDown(SDL_Scancode key);

private:
    static const Uint8* keyboardState;
};
