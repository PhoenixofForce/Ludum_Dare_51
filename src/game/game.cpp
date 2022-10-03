#include "game.h"

#define STAT_TIME 5000
#define TRANS_TIME 200
#define PAUSE_TIME 500

std::vector<std::string> maps{"level_1", "level_2", "level_3", "level_4", "level_5"};
std::vector<Request> requests {
  {"goat", std::vector<Rect>{{462, 508, 162, 183}}},
  {"u", std::vector<Rect>{{397, 352, 62, 124}, {623, 343, 62, 141}, {462, 508, 162, 75}}},
  {"w", std::vector<Rect>{{397, 352, 62, 200}, {623, 343, 62, 200}, {489, 456, 107, 45}}},
  {"trident", std::vector<Rect>{{425, 454, 290, 100}}},
  {"cotlet", std::vector<Rect>{{397, 352, 62, 124}, {623, 343, 62, 141}}},
  {"full", std::vector<Rect>{{400, 454, 290, 150}}},
  {"lip", std::vector<Rect>{{489, 456, 107, 45}}},
  {"chin", std::vector<Rect>{{462, 508, 162, 75}}}
};

Game::Game(SDL_Renderer* renderer, int windowWidth, int windowHeight) 
: renderer{renderer}, music{Mix_LoadMUS("res/cutter.wav")}, window_width{windowWidth}, window_height{windowHeight}, map{renderer, window_width, window_height, ""}
{  
    std::shuffle(requests.begin(), requests.end(), std::default_random_engine{});
    std::shuffle(maps.begin(), maps.end(), std::default_random_engine{});

    texture::loadSpriteSheetPng(renderer, "cover", "cover");
    texture::loadSpriteSheetPng(renderer, "requests", "requests");
    texture::loadSpriteSheetPng(renderer, "countdown", "countdown");
    texture::loadSpriteSheetPng(renderer, "cutter", "cutter");
    texture::loadSpriteSheetPng(renderer, "stars", "stars");
    texture::loadSpriteSheetPng(renderer, "bg", "bg");

    countdown = {1000, std::vector<std::string>{"countdown_10", "countdown_9", "countdown_8", "countdown_7", "countdown_6", "countdown_5", "countdown_4", "countdown_3", "countdown_2", "countdown_1", "countdown_0"}};
}

void Game::update(long dt, std::map<int, bool> pressedKeys) {
    timeRunning += dt;
    mouseDown = pressedKeys[-101];

    if(state == 0) {
        curtainPos = 0;
        firstLoad = false;

        if(timeRunning >= 10000) {
            std::cout << std::endl << std::endl << std::endl << "10s passed" << std::endl;
            timeRunning = 1;
            state = 1;
        }
        
        if(mouseDown) {
            cutHair();

            if(!playingMusic) {
                playingMusic = true;
                Mix_PlayMusic(music, -1);
            }
        } else {
            if(playingMusic) {
                playingMusic = false;
                Mix_PauseMusic();
            }
        }
    }

    if(state == 1) {
        static bool reloadMap = false;

        if(playingMusic) {
            playingMusic = false;
            Mix_PauseMusic();
        }

        if(timeRunning > PAUSE_TIME && timeRunning <= TRANS_TIME + PAUSE_TIME) {
            if(reloadMap) {
                int hairInside = 0;
                int hairOutside = 0;
                countHair(hairInside, hairOutside);

                if(hairInside == benchmarkInside && hairOutside == benchmarkOutside) {
                    score = 0;
                } else {
                    std::cout << hairInside << "/" << benchmarkInside << " hairs kept inside" << std::endl;
                    std::cout << hairOutside << "/" << benchmarkOutside << " hairs left outside" << std::endl;

                    hairOutside = benchmarkOutside - hairOutside;

                    float insideAccuracy = 1.0 * hairInside / benchmarkInside;
                    float outsideAccuracy = 1.0 * hairOutside/ benchmarkOutside;

                    float balancedAccuracy = (insideAccuracy + 2 * outsideAccuracy) / 3.0;

                    std::cout << "----------------" << std::endl;
                    std::cout << "inside%:  " << insideAccuracy << std::endl;
                    std::cout << "outside%: " << outsideAccuracy << std::endl;
                    std::cout << "total%:   " << balancedAccuracy << std::endl;
                    std::cout << "score:    " << (balancedAccuracy * 5.0) << std::endl;

                    score = std::round(balancedAccuracy * 5.0);
                    score = std::min(5, score);
                }

                std::cout << std::endl << "SCORE: " << score << std::endl << std::endl;
            }

            curtainPos = (1.0 * (timeRunning - PAUSE_TIME) / TRANS_TIME) * window_height;
            reloadMap = false;
        }

        if(timeRunning > TRANS_TIME + PAUSE_TIME && timeRunning <= 1500) {
            curtainPos = window_height;

            if(timeRunning >= 1100 && reloadMap == false) {
                //load new map

                std::string currentMap{ maps.at(0) };
                maps.erase(maps.begin());
                maps.push_back(currentMap);

                texture::deleteSheet(map.getSheetName());
                map = GameMap{renderer, window_width, window_height, maps.at(0)};

                Request placeHolder{ requests.at(0) };
                requests.erase(requests.begin());
                requests.push_back(placeHolder);

                countHair(benchmarkInside, benchmarkOutside);

                reloadMap = true;
            }
        }

        if(timeRunning > STAT_TIME - TRANS_TIME) {
            curtainPos = (1.0 * (STAT_TIME - timeRunning) / TRANS_TIME) * window_height;
            countdown.reset();
        }

        if(timeRunning >= STAT_TIME) {
            curtainPos = 0;
            timeRunning = 1;
            state = 0;
            countdown.reset();
        }
    }
}

void Game::render(SDL_Renderer* renderer) {
    fillRect(renderer, {0, 0, window_width, window_height}, {107, 62, 117});

    vec::vec2f offset{
        position.x - window_width / 2,
        position.y - window_height / 2
    };
    offset.normalize(-12);

    if(mouseDown) {
        offset.x += std::sin(1.0 * timeRunning / 10.0) * 2;
        offset.y += std::sin(1.0 * timeRunning / 10.0 + 3.141592 / 4) * 2;
    }

    drawImage(renderer, "bg_bg", vec::vec2f{});
    drawImage(renderer, "bg_bg", offset);

    map.render(renderer);
    drawImage(renderer, "requests_" + requests.at(0).name, vec::vec2f{window_width - 300, 0}, 0.25f);
    drawImage(renderer, countdown.getTexture(), vec::vec2f{}, 0.15f);

    if(state == 0) {
        std::string texture = "cutter_";
        texture += (mouseDown? "on": "off");
        drawImage(renderer, texture, vec::vec2f{position.x - 125, position.y - 100}, 0.25f);
    } 

    if(!firstLoad) fillRect(renderer, {0, 0, window_width, curtainPos}, {63, 101, 166});
    if(state == 1 && timeRunning >= TRANS_TIME + PAUSE_TIME && timeRunning <= STAT_TIME - TRANS_TIME) {
        if(!firstLoad) drawImage(renderer, "stars_" + std::to_string(score), vec::vec2f{window_width, window_height} / 2 - vec::vec2f{250, 250}, 0.5);
        else drawImage(renderer, "cover_cover", vec::vec2f{}, 1);
    }
}

void Game::setMouse(const int& mouseX, const int& mouseY) {
    position = {mouseX, mouseY};
}

void Game::cutHair() {
    Rect cutter{position.x - 50, position.y - 100, 100, 25};

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

void Game::countHair(int& hairInside, int& hairOutside) {
    hairInside = 0;
    hairOutside = 0;

    for(const Entity& e: map.getEntities()) {
        bool found = false;
        for(const Rect& r: requests.at(0).hitboxes) {
            if(r.intersects(e.hitbox.x, e.hitbox.y)) {
                hairInside++;
                found = true;
            }
        }

        if(!found) hairOutside++;
    }
}