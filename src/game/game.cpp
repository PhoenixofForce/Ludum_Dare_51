#include "game.h"

Game::Game(SDL_Renderer* renderer, int windowWidth, int windowHeight) {
    window_width = windowWidth;
    winow_height = windowHeight;
    
    texture::loadSpriteSheetPng(renderer, "sheet");
    texture::loadSpriteSheetPng(renderer, "textures_unpacked");

    map = GameMap(scale, "res/test2.map");
}

void Game::update(long dt, std::map<int, bool> pressedKeys) {
    int dx = (pressedKeys[SDLK_d] - pressedKeys[SDLK_a]);
    int dy = (pressedKeys[SDLK_s] - pressedKeys[SDLK_w]);

    position += vec::vec2f{dx, dy}.normalize(5);
}

void Game::render(SDL_Renderer* renderer) {
    vec::vec2f offset{ position - vec::vec2f{ window_width, winow_height} / 2 };

    map.render(renderer, offset);
    drawImage(renderer, grass.getTexture(), position - offset, scale);
}

int Game::getScale() {
    return scale;
}