#pragma once
#include <SDL2/SDL.h>
#include <string>

class Sprite {
public:
    SDL_Texture* texture;

    Sprite(const std::string& path);

    void draw(int x, int y, int scale = 2);
    void setAnimation(int fw, int fh, int count);

private:
    int width, height;

    int frameWidth = 0;
    int frameHeight = 0;
    int frameCount = 1;
    int currentFrame = 0;

    float animationSpeed = 10.0f;
    float frameTimer = 0.0f;
};
