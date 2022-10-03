#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>

#include "maploader.h"
#include "../../util/random.h"
#include "../../util/structs/matrix.h"
#include "../entities/entity.h"
#include "../../util/structs/vec2f.h"
#include "../../rendering.h"

class GameMap {

public:
    GameMap(SDL_Renderer* renderer, int scale, const std::string& name);

    void update(long dt, std::map<int, bool> pressedKeys);
    void render(SDL_Renderer* renderer, vec::vec2f cameraPosition = vec::vec2f{});

    std::vector<Entity>& getEntities();

private:
    int tileSize;
    int scale;

    std::string textureSheet{};

    std::vector<Entity> entities;

    void addGameObject(IDMapper idMaps, float depth, int texture, float x, float y);
};

#endif

