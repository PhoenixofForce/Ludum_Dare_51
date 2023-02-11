#ifndef MAP_H
#define MAP_H

#include "maploader.h"
#include "../../util/random.h"
#include "../../util/structs/matrix.h"
#include "../entities/entity.h"
#include "../../util/structs/vec2f.h"
#include "../../rendering.h"

class GameMap {

public:
    GameMap(int windowWidth, int windowHeight, const std::string& name);
    ~GameMap();

    void update(long dt, std::map<int, bool> pressedKeys);
    void render(vec::vec2f cameraPosition = vec::vec2f{});

    std::vector<Entity>& getEntities();
    const std::string& getSheetName();

    void handleResize(const int& newWidth, const int& newHeight);
    float getScale();

private:
    int tileSize{1};
    float scale{1};
    int windowWidth{0};
    int windowHeight{0};

    int entitiesLoaded = 0;

    std::string textureSheet{};
    std::vector<Entity> entities;

    void addGameObject(IDMapper idMaps, float depth, int texture, float x, float y);
};

#endif

