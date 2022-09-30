#include "map.h"

GameMap::GameMap(int scale, const std::string& name) {
    this->scale = scale;

    if(name.length() > 0) loadMap(name, 
        [this](int tileSize, std::vector<Tag> tags) { this->tileSize = tileSize; },
        [this](IDMapper mapper, float d, Matrix<int> map) { setTerrain(mapper, d, map); },
        [this](IDMapper mapper, float d, int t, float x, float y, std::vector<Tag> tags){ addGameObject(mapper, d, t, x * tileSize, y * tileSize); },
        [](float x1, float y1, float x2, float y2, std::vector<Tag> tags){}
    );
}

void GameMap::update(long dt, std::map<int, bool> pressedKeys) {}

void GameMap::render(SDL_Renderer* renderer, vec::vec2f cameraPosition) {
    for(int x = 0; x < terrain.getWidth(); x++) {
        for(int y = 0; y < terrain.getHeight(); y++) {
            const std::string& texture { terrain.get(x, y) };
            vec::vec2f pos{x, y};
            pos *= scale * tileSize;
            if(texture.length() > 0) drawImage(renderer, texture, pos - cameraPosition, scale);
        }
    }

    for(const Entity& e: entities) {
        drawImage(renderer, e.sprite.getTexture(), e.position - cameraPosition, scale);
    }
}

void GameMap::setTerrain(IDMapper mapper, float d, Matrix<int> map) {
    terrain = Matrix<std::string>(map.getWidth(), map.getHeight());
    for(int x = 0; x < map.getWidth(); x++) {
        for(int y = 0; y < map.getHeight(); y++) {
            int texture = map.get(x, y);
            terrain.set(x, y, texture == 0? "": mapper[texture]);
        }
    }
}

void GameMap::addGameObject(IDMapper idMaps, float depth, int texture, float x, float y) {
    vec::vec2f pos{ x * scale, y * scale };
    std::string textures[1]{ idMaps[texture] };

    Sprite sprite{100, textures};
    entities.push_back({pos, sprite });
}

