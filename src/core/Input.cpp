#include "Input.h"

const Uint8* Input::keyboardState = nullptr;

void Input::update() {
    keyboardState = SDL_GetKeyboardState(NULL);
}

bool Input::keyDown(SDL_Scancode key) {
    return keyboardState && keyboardState[key];
}
