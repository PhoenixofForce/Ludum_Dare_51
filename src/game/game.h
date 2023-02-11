#ifndef GAME_H
#define GAME_H

#include "raylib.h"

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
    Game(int window_width, int window_height);

    void update(long dt, std::map<int, bool> pressedKeys);
    void render();

    void setMouse(const int& mouseX, const int& mouseY);
    void handleResize(const int& newWidth, const int& newHeight);

private: 
    int state = 1; //0 - cut, 1 - stats
    int curtainPos = 0;

    long timeRunning = 1101;
    int window_width = 0;
    int window_height = 0;

    int benchmarkInside;
    int benchmarkOutside;

    int score = 0;
    int totalScore = 0;

    Sound music;
    Sound backgroundNoise;

    bool firstLoad = true;
    bool playingMusic = false;
    bool mouseDown = false;

    GameMap map;
    std::vector<Entity> particles{};

    vec::vec2f position{0, 0};
    vec::vec2f lastPosition{0, 0};

    Sprite countdown{1000, "", 0};

    void cutHair();
    void countHair(int& hairInside, int& hairOutside);
};

#endif