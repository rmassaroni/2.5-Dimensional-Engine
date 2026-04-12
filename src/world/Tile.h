#pragma once

struct Tile {
    int id;
    bool solid;
    int height;

    Tile(int id = 0, bool solid = false, int height = 0)
        : id(id), solid(solid), height(height) {}
};
