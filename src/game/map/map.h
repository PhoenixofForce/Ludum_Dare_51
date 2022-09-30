#ifndef MAP_H
#define MAP_H

#include "maploader.h"
#include "../../util/structs/matrix.h"
#include "../entities/entity.h"
#include "../../util/structs/vec2f.h"
#include "../../rendering.h"

class GameMap {

public:
    GameMap(int scale, const std::string& name);

    void update(long dt, std::map<int, bool> pressedKeys);
    void render(SDL_Renderer* renderer, vec::vec2f cameraPosition);

private:
    int tileSize;
    int scale;

    Matrix<std::string> terrain{1, 1};
    std::vector<Entity> entities;

    void setTerrain(IDMapper mapper, float d, Matrix<int> map);
    void addGameObject(IDMapper idMaps, float depth, int texture, float x, float y);
};

#endif

