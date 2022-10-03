#include "game.h"

Game::Game(SDL_Renderer* renderer, int windowWidth, int windowHeight) 
: window_width{windowWidth}, window_height{window_height}, map{renderer, scale, "res/testMap.map"}
{    

}

void Game::update(long dt, std::map<int, bool> pressedKeys) {
    Rect cutter{position.x - 75, position.y - 25, 150, 50};
    
    bool mouseDown = pressedKeys[-101];
    if(mouseDown) {
        std::vector<int> toDelete{};
        for(int i = 1; i < map.getEntities().size(); i++) {
            Entity& e = map.getEntities().at(i);

            //if(cutter.intersects({e.position.xi(), e.position.yi(), e.hitbox.w, e.hitbox.h})) toDelete.push_back(i);
            if(cutter.intersects(e.hitbox.x, e.hitbox.y)) toDelete.push_back(i);
        }

        for(int i = toDelete.size() - 1; i >= 0; i--) {
            map.getEntities().erase(map.getEntities().begin() + toDelete.at(i));
        }   
    } 
}

void Game::render(SDL_Renderer* renderer) {
    fillRect(renderer, {0, 0, window_width, window_height}, {107, 62, 117});
    map.render(renderer);

    Rect cutter{position.x - 75, position.y - 25, 150, 50};
    fillRect(renderer, cutter, {0, 255, 0});
}

void Game::setMouse(const int& mouseX, const int& mouseY) {
    position = {mouseX, mouseY};
}

int Game::getScale() {
    return scale;
}