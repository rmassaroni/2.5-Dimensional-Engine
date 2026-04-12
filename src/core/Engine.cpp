#include "Engine.h"
#include "Input.h"
#include "Time.h"
#include <SDL2/SDL_image.h>

bool Engine::init() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow("Pixel Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600, 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    scene.init(renderer);

    running = true;
    return true;
}

void Engine::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            running = false;
    }
}

void Engine::update() {
    scene.update();
}

void Engine::render() {
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    scene.render();

    SDL_RenderPresent(renderer);
}

void Engine::run() {
    while (running) {
        Time::update();
        Input::update();

        handleEvents();
        update();
        render();

        SDL_Delay(1);
    }
}

void Engine::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
