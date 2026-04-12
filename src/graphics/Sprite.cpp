#include "Sprite.h"
#include "Renderer.h"
#include "Camera.h"
#include "core/Time.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Sprite::Sprite(const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());

    if (!surface) {
        std::cout << "Missing asset: " << path << "\n";
        return;
    }

    texture = SDL_CreateTextureFromSurface(Renderer::sdlRenderer, surface);

    width = surface->w;
    height = surface->h;

    SDL_FreeSurface(surface);
}

void Sprite::setAnimation(int fw, int fh, int count) {
    frameWidth = fw;
    frameHeight = fh;
    frameCount = count;
}

void Sprite::draw(int x, int y, int scale) {
    if (frameCount > 1) {
        frameTimer += Time::deltaTime;
        if (frameTimer >= 1.0f / animationSpeed) {
            currentFrame = (currentFrame + 1) % frameCount;
            frameTimer = 0.0f;
        }
    }

    SDL_Rect src;

    if (frameWidth > 0) {
        src = { currentFrame * frameWidth, 0, frameWidth, frameHeight };
    } else {
        src = {0, 0, width, height};
    }

    SDL_Rect dst = {
        x - Camera::x,
        y - Camera::y,
        src.w * scale,
        src.h * scale
    };

    SDL_RenderCopy(Renderer::sdlRenderer, texture, &src, &dst);
}
