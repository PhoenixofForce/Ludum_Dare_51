#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

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

    void setMouse(const int& mouseX, const int& mouseY);

private: 
    SDL_Renderer* renderer;
    Mix_Chunk* music;
    Mix_Music* backgroundNoise;

    int state = 1; //0 - cut, 1 - stats
    int curtainPos = 0;

    long timeRunning = 1101;
    int window_width = 0;
    int window_height = 0;

    int benchmarkInside;
    int benchmarkOutside;

    int score = 0;

    bool firstLoad = true;
    bool playingMusic = false;
    bool mouseDown = false;

    GameMap map;
    vec::vec2f position{0, 0};
    Sprite countdown{1000, "", 0};

    void cutHair();
    void countHair(int& hairInside, int& hairOutside);
};

#endif