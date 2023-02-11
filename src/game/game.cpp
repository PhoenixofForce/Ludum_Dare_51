#include "game.h"

//DEFAULT_SCALE is the intended map scale on default resolution
#define DEFAULT_SCALE 0.53333336114883423f
#define STAT_TIME 5000
#define TRANS_TIME 200
#define PAUSE_TIME 500

std::vector<std::string> maps{"level_1", "level_2", "level_3", "level_4", "level_5"};
std::vector<Request> requests {
  {"goat", std::vector<Rect>{{462, 458, 162, 183}}},
  {"u", std::vector<Rect>{{397, 352, 62, 124}, {623, 343, 62, 141}, {462, 508, 162, 75}}},
  {"w", std::vector<Rect>{{397, 352, 62, 200}, {623, 343, 62, 200}, {459, 416, 167, 55}}},
  {"trident", std::vector<Rect>{{425, 454, 290, 100}, {489, 416, 107, 55}}},
  {"cotlet", std::vector<Rect>{{397, 352, 62, 124}, {623, 343, 62, 141}}},
  {"full", std::vector<Rect>{{400, 416, 290, 190}}},
  {"lip", std::vector<Rect>{{489, 416, 107, 55}}},
  {"chin", std::vector<Rect>{{462, 508, 162, 75}}}

};

Game::Game(int windowWidth, int windowHeight) 
: music{LoadSound("res/cutter.wav")}, backgroundNoise{LoadSound("res/backgroundNoise.wav")},
 window_width{windowWidth}, window_height{windowHeight}, map{window_width, window_height, ""}
{  

    PlaySound(backgroundNoise);

    std::shuffle(requests.begin(), requests.end(), std::default_random_engine{});
    std::shuffle(maps.begin(), maps.end(), std::default_random_engine{});

    texture::loadSpriteSheetPng("cover", "cover");
    texture::loadSpriteSheetPng("requests", "requests");
    texture::loadSpriteSheetPng("countdown", "countdown");
    texture::loadSpriteSheetPng("cutter", "cutter");
    texture::loadSpriteSheetPng("stars", "stars");
    texture::loadSpriteSheetPng("bg", "bg");

    countdown = {1000, std::vector<std::string>{"countdown_10", "countdown_9", "countdown_8", "countdown_7", "countdown_6", "countdown_5", "countdown_4", "countdown_3", "countdown_2", "countdown_1", "countdown_0"}};
}

void Game::update(long dt, std::map<int, bool> pressedKeys) {
    timeRunning += dt;
    mouseDown = pressedKeys[-101];

    if(state == 0) { //Cutting phase
        curtainPos = 0;
        firstLoad = false;

        //update particles
        for(int i = particles.size() - 1; i >= 0; i--) {
            Entity& p{ particles.at(i) };
            p.hitbox.x += p.position.xi();
            p.hitbox.y += p.position.yi();

            p.position.y += 2;

            if(p.hitbox.y > window_height) {
                particles.erase(particles.begin() + i);
            }
        }

        //change to evaluation stage
        if(timeRunning >= 10000) {
            std::cout << std::endl << std::endl << std::endl << "10s passed" << std::endl;
            timeRunning = 1;
            state = 1;
        }
        
        //Cut hair and play razor sounds
        if(mouseDown) {
            cutHair();

            if(!playingMusic) {
                playingMusic = true;
                PlaySound(music);
            }
        } else {
            if(playingMusic) {
                playingMusic = false;
                StopSound(music);
            }
        }
    }

    if(state == 1) {    //Eval Stage
        static bool reloadMap = false;

        //Stop razor sounds
        if(playingMusic) {
            playingMusic = false;
            StopSound(music);
        }

        if(timeRunning > PAUSE_TIME && timeRunning <= TRANS_TIME + PAUSE_TIME) {
            if(reloadMap) {
                particles.clear();

                int hairInside = 0;
                int hairOutside = 0;
                countHair(hairInside, hairOutside);

                //calculate score
                if((hairInside == benchmarkInside && hairOutside == benchmarkOutside) || hairInside == 0) {
                    score = 0;
                } else {
                    std::cout << hairInside << "/" << benchmarkInside << " hairs kept inside" << std::endl;
                    std::cout << hairOutside << "/" << benchmarkOutside << " hairs left outside" << std::endl;

                    hairOutside = benchmarkOutside - hairOutside;

                    float insideAccuracy = 1.0 * hairInside / benchmarkInside;
                    float outsideAccuracy = 1.0 * hairOutside/ benchmarkOutside;

                    float balancedAccuracy = (insideAccuracy + outsideAccuracy) / 2.0;

                    std::cout << "----------------" << std::endl;
                    std::cout << "inside%:  " << insideAccuracy << std::endl;
                    std::cout << "outside%: " << outsideAccuracy << std::endl;
                    std::cout << "total%:   " << balancedAccuracy << std::endl;
                    std::cout << "score:    " << (balancedAccuracy * 5.0) << std::endl;

                    score = std::round(balancedAccuracy * 4.0);
                    score = std::min(4, score) + 1;
                }
                totalScore += score;

                std::cout << std::endl << "SCORE: " << score << std::endl << std::endl;
            }

            //pull curtain down
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

                std::cout << map.getSheetName() << " ";
                texture::deleteSheet(map.getSheetName());
                map = GameMap{window_width, window_height, maps.at(0)};

                Request placeHolder{ requests.at(0) };
                requests.erase(requests.begin());
                requests.push_back(placeHolder);

                countHair(benchmarkInside, benchmarkOutside);

                reloadMap = true;
            }
        }

        //pull curtain up
        if(timeRunning > STAT_TIME - TRANS_TIME) {
            curtainPos = (1.0 * (STAT_TIME - timeRunning) / TRANS_TIME) * window_height;
            countdown.reset();
        }

        //change to cutting stage
        if(timeRunning >= STAT_TIME) {
            curtainPos = 0;
            timeRunning = 1;
            state = 0;
            countdown.reset();
        }
    }
}

void Game::render() {
    fillRect({0, 0, 1 * window_width, 1 * window_height}, Color{107, 62, 117, 255});

    //background offset, so that the background moves a little when the mouse moves
    vec::vec2f offset{
        position.x - window_width / 2,
        position.y - window_height / 2
    };
    offset.normalize(-12);

    //screenshake when the razor is on
    if(mouseDown) {
        offset.x += std::sin(1.0 * timeRunning / 10.0) * 2;
        offset.y += std::sin(1.0 * timeRunning / 10.0 + 3.141592 / 4) * 2;
    }

    //draws the background with and without the offset, so that there are no black parts
    float bgScale = 1;
    {
        const Rect& bgBounds = texture::getSpriteSheetBounds("bg_bg");
        float scaleX = 1.0f * window_width / bgBounds.w;
        float scaleY = 1.0f * window_height / bgBounds.h;
        bgScale = std::max(scaleX, scaleY);
    }

    drawImage("bg_bg", vec::vec2f{}, bgScale);
    drawImage("bg_bg", offset, bgScale);

    //render map, hair particles, requests and countdown
    map.render();
    for(Entity& e: particles) {
        drawImage(e.sprite.getTexture(), {e.hitbox.x, e.hitbox.y}, map.getScale());
    }
    drawImage("requests_" + requests.at(0).name, vec::vec2f{window_width - 300, 0}, 0.25f);
    drawImage(countdown.getTexture(), vec::vec2f{}, 0.15f);

    
    // Draw Hitboxes of the current request
    /*
    float razorScale = (map.getScale() / DEFAULT_SCALE);
    for(Rect& r2: requests.at(0).hitboxes) {
        Rect r{ (r2.x - 1080/2) * razorScale + window_width/2, r2.y * razorScale, r2.w * razorScale, r2.h * razorScale };
        drawRect(renderer, r, {255, 0, 0});
    }
    */

    //draws the razor
    if(state == 0) {
        std::string texture = "cutter_";
        texture += (mouseDown? "on": "off");

        float razorScale = (map.getScale() / DEFAULT_SCALE);
        drawImage(texture, vec::vec2f{position.x - 125 * razorScale, position.y - 100 * razorScale}, 0.25f * razorScale);

        //draws razor hitbox
        /*
        Rect cutter{position.x - 40 * razorScale, position.y - 95 * razorScale, 80 * razorScale, 25 * razorScale};
        drawRect(renderer, cutter, {255, 0, 0});
        */
    } 

    if(!firstLoad) fillRect({0, 0, window_width, curtainPos}, Color{63, 101, 166, 255});
    if(state == 1 && timeRunning >= TRANS_TIME + PAUSE_TIME && timeRunning <= STAT_TIME - TRANS_TIME) {
        //draw the score and total score
        if(!firstLoad) {
            drawImage("stars_" + std::to_string(score), vec::vec2f{window_width, window_height} / 2 - vec::vec2f{250, 250}, 0.5);

            //total score
            drawImage("stars_1", vec::vec2f{window_width - 150, -35}, 0.15);

            std::string totalString{ std::to_string(totalScore) };
            int x = window_width - 150;
            for(int i = totalString.size() - 1; i >= 0; i--) {
                std::string letterTexture{ "countdown_" };
                letterTexture += totalString.at(i);

                drawImage(letterTexture, vec::vec2f{x, 0}, 0.075f);
                x -= 40;
            }

        }
        //if the game loads the first time, draw the cover image instead
        else {
            const Rect& bounds{ texture::getSpriteSheetBounds("cover_cover")};
            drawImage("cover_cover", vec::vec2f{(window_width - bounds.w * bgScale) / 2, (window_height - bounds.h * bgScale) / 2}, bgScale);
        }
    }
}

void Game::handleResize(const int& newWidth, const int& newHeight) {
    window_width = newWidth;
    window_height = newHeight;
    map.handleResize(newWidth, newHeight);
}

void Game::setMouse(const int& mouseX, const int& mouseY) {
    lastPosition = position;
    position = {mouseX, mouseY};
}

void Game::cutHair() {
    float razorScale = (map.getScale() / DEFAULT_SCALE);
    Rect cutter{position.x - 40 * razorScale, position.y - 95 * razorScale, 80 * razorScale, 25 * razorScale};

    std::vector<int> toDelete{};
    for(int i = 1; i < map.getEntities().size(); i++) {
        Entity& e = map.getEntities().at(i);

        //if(cutter.intersects({e.position.xi(), e.position.yi(), e.hitbox.w, e.hitbox.h})) toDelete.push_back(i);  //alternative intersection method
        if(cutter.intersects(e.hitbox.x, e.hitbox.y)) toDelete.push_back(i);
    }

    vec::vec2f mouseDX{ position - lastPosition };
    for(int i = toDelete.size() - 1; i >= 0; i--) {
        Entity deletedEntity{ map.getEntities().at(toDelete.at(i)) };

        float flyingDirection = deletedEntity.position.x - position.x;
        Entity particle{
            vec::vec2f{flyingDirection + rnd::random(0, 5) * (flyingDirection < 0? -1: 1), 10}.normalize(10), 
            deletedEntity.sprite, 
            Rect{deletedEntity.position.xi(), deletedEntity.position.yi(), 1, 1} 
        };
        particle.position.y = -10 * (mouseDX.y < 0? 1: -1);

        particles.push_back(
            particle
        );

        map.getEntities().erase(map.getEntities().begin() + toDelete.at(i));
    }   
}

void Game::countHair(int& hairInside, int& hairOutside) {
    hairInside = 0;
    hairOutside = 0;

    float razorScale = (map.getScale() / DEFAULT_SCALE);
    for(const Entity& e: map.getEntities()) {
        bool found = false;
        for(const Rect& r2: requests.at(0).hitboxes) {

            //calculate new hitboxPosition based on scale
            Rect r{ (r2.x - 1080/2) * razorScale + window_width/2, r2.y * razorScale, r2.w * razorScale, r2.h * razorScale };

            if(r.intersects(e.hitbox.x, e.hitbox.y)) {
                hairInside++;
                found = true;
            }
        }

        if(!found) hairOutside++;
    }
}

