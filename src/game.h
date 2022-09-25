#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

#include "rendering.h"

#include "data/rect.h"
#include "data/color.h"
#include "data/vec2f.h"
#include "data/sprite.h"

#include "util/random.h"

class Game {

public: 
    Game(SDL_Renderer* renderer);

    void update(long dt, std::map<int, bool> pressedKeys);
    void render(SDL_Renderer* renderer);


private: 
    vec::vec2f position{0, 0};
    Sprite grass{500, "grass", 2};

};

#endif