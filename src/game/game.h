#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

#include "../rendering.h"
#include "entities/entity.h"

#include "../util/structs/vec2f.h"
#include "../assets/sprite.h"

#include "../util/random.h"

#include "map/map.h"

class Game {

public: 
    Game(SDL_Renderer* renderer, int window_width, int window_height);

    void update(long dt, std::map<int, bool> pressedKeys);
    void render(SDL_Renderer* renderer);

    int getScale();

private: 
    int scale = 5;
    int window_width = 0;
    int winow_height = 0;

    GameMap map{scale, ""};
    vec::vec2f position{144, 4};
    Sprite grass{500, "sheet_grass", 2};

};

#endif