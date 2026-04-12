#pragma once

struct Tile {
    int id;
    bool solid;

    Tile(int id = 0, bool solid = false)
        : id(id), solid(solid) {}
};
