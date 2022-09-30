#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

#include "rendering.h"
#include "entity.h"

#include "data/rect.h"
#include "data/color.h"
#include "data/vec2f.h"
#include "data/sprite.h"

#include "util/random.h"

#include "map/maploader.h"

class Game {

public: 
    Game(SDL_Renderer* renderer);

    void update(long dt, std::map<int, bool> pressedKeys);
    void render(SDL_Renderer* renderer);

private: 
    vec::vec2f position{144, 4};
    Sprite grass{500, "sheet_grass", 2};

    int scale = 5;
    int tileSize = 1;
    std::vector<Entity> entities{};

    void setMapSettings(int ts, std::vector<Tag> tags);
    void addGameObject(IDMapper idMaps, float depth, int texture, float x, float y);

};

#endif