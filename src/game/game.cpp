#include "game.h"

#define STAT_TIME 5000
#define TRANS_TIME 200

std::vector<std::string> maps{"testMap"};

Game::Game(SDL_Renderer* renderer, int windowWidth, int windowHeight) 
: renderer{renderer}, window_width{windowWidth}, window_height{windowHeight}, map{renderer, window_width, window_height, scale, maps.at(0)}
{    }

void Game::update(long dt, std::map<int, bool> pressedKeys) {
    timeRunning += dt;

    if(state == 0) {
        curtainPos = 0;

        if(timeRunning >= 10000) {
            std::cout << "10s passed" << std::endl;
            timeRunning = 1;
            state = 1;
        }

        
        bool mouseDown = pressedKeys[-101];
        if(mouseDown) {
            cutHair();
        } 
    }

    if(state == 1) {
        if(timeRunning <= TRANS_TIME) {
            curtainPos = (1.0 * timeRunning / TRANS_TIME) * window_height;
            //calc score here
        }

        if(timeRunning > TRANS_TIME && timeRunning <= 1500) {
            curtainPos = window_height;

            if(timeRunning >= 600) {
            //load new map
            std::string currentMap{ maps.at(0) };
            maps.erase(maps.begin());
            maps.push_back(currentMap);
            texture::deleteSheet(map.getSheetName());
            map = GameMap{renderer, window_width, window_height, scale, maps.at(0)};
            }
        }

        if(timeRunning > STAT_TIME - TRANS_TIME) {
            curtainPos = (1.0 * (STAT_TIME - timeRunning) / TRANS_TIME) * window_height;
        }

        if(timeRunning >= STAT_TIME) {
            curtainPos = 0;
            timeRunning = 1;
            state = 0;
        }
    }
}

void Game::cutHair() {
    Rect cutter{position.x - 75, position.y - 25, 150, 50};

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

void Game::render(SDL_Renderer* renderer) {
    fillRect(renderer, {0, 0, window_width, window_height}, {107, 62, 117});
    map.render(renderer);

    Rect cutter{position.x - 75, position.y - 25, 150, 50};
    fillRect(renderer, cutter, {0, 255, 0});

    fillRect(renderer, {0, 0, window_width, curtainPos}, {255, 62, 117});
}

void Game::setMouse(const int& mouseX, const int& mouseY) {
    position = {mouseX, mouseY};
}

int Game::getScale() {
    return scale;
}