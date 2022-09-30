#include "game.h"

Game::Game(SDL_Renderer* renderer) {
    texture::loadSpriteSheetPng(renderer, "sheet");
    texture::loadSpriteSheetPng(renderer, "textures_unpacked");

    loadMap("./res/test2.map", 
        [this](int tileSize, std::vector<Tag> tags){ setMapSettings(tileSize, tags); },
        [this](IDMapper mapper, float d, Matrix<int> map){
            for(int x = 0; x < map.getWidth(); x++) {
                for(int y = 0; y < map.getHeight(); y++) {
                    int texture = map.get(x, y);
                    if(texture > 0) {
                        addGameObject(mapper, d, texture, x * tileSize, y * tileSize);
                    }
                }
            }

        },
        [this](IDMapper mapper, float d, int t, float x, float y, std::vector<Tag> tags){ addGameObject(mapper, d, t, x * tileSize, y * tileSize); },
        [](float x1, float y1, float x2, float y2, std::vector<Tag> tags){}
    );
}

void Game::update(long dt, std::map<int, bool> pressedKeys) {
    int dx = (pressedKeys[SDLK_d] - pressedKeys[SDLK_a]);
    int dy = (pressedKeys[SDLK_s] - pressedKeys[SDLK_w]);

    position += vec::vec2f{dx, dy}.normalize(5);
}

void Game::render(SDL_Renderer* renderer) {
    for(const Entity& e: entities) {
        drawImage(renderer, e.sprite.getTexture(), e.position, scale);
    }

    drawImage(renderer, grass.getTexture(), position, scale);
}

void Game::setMapSettings(int ts, std::vector<Tag> tags) {
    tileSize = ts;
}

void Game::addGameObject(IDMapper idMaps, float depth, int texture, float x, float y) {
    vec::vec2f pos{ x * scale, y * scale };
    std::string textures[1]{ idMaps[texture] };

    Sprite sprite{100, textures};
    entities.push_back({pos, sprite });
}

