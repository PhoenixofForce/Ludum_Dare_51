#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

#include "../rendering.h"
#include "entities/entity.h"

#include "../util/structs/vec2f.h"
#include "../assets/sprite.h"
#include "../assets/TextureHandler.h"

#include "../util/random.h"

#include "map/map.h"

class Game {

public: 
    Game(SDL_Renderer* renderer, int window_width, int window_height);

    void update(long dt, std::map<int, bool> pressedKeys);
    void render(SDL_Renderer* renderer);

    int getScale();
    void setMouse(const int& mouseX, const int& mouseY);

private: 
    SDL_Renderer* renderer;

    int state = 0; //0 - cut, 1 - stats
    int curtainPos = 0;

    long timeRunning = 1;
    int scale = 5;
    int window_width = 0;
    int window_height = 0;

    GameMap map;
    vec::vec2f position{144, 4};

    void cutHair();
};

#endif