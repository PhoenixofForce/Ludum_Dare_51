#include "map.h"

GameMap::GameMap(SDL_Renderer* renderer, int inWindowWidth, int inWindowHeight, const std::string& name) 
: scale(0.5f), windowWidth(inWindowWidth), windowHeight(inWindowHeight)
{

    if(name.length() > 0) loadMap("res/" + name + ".map", 
        [this, renderer](int tileSize, std::vector<Tag> tags) { 
            this->tileSize = tileSize;
            for(const Tag& tag: tags) {
                if(tag.header == "import") {
                    texture::loadSpriteSheetPng(renderer, tag.body);
                    textureSheet = tag.body;
                }
            }    
        },
        [this](IDMapper mapper, float d, Matrix<int> map) { },
        [this](IDMapper mapper, float d, int t, float x, float y, std::vector<Tag> tags){ addGameObject(mapper, d, t, x * tileSize, y * tileSize); },
        [](float x1, float y1, float x2, float y2, std::vector<Tag> tags){}
    );
}

void GameMap::update(long dt, std::map<int, bool> pressedKeys) {}

void GameMap::render(SDL_Renderer* renderer, vec::vec2f cameraPosition) {
    //face
    drawImage(renderer, entities[0].sprite.getTexture(), entities[0].position - cameraPosition, scale);

    //outline
    for(int i = 1; i < entities.size(); i++) {
        const Entity& e{ entities.at(i) };
        drawImage(renderer, e.sprite.getTexture() + "_outline", e.position - cameraPosition, scale);
    }

    //hair
    for(int i = 1; i < entities.size(); i++) {
        const Entity& e{ entities.at(i) };
        drawImage(renderer, e.sprite.getTexture(), e.position - cameraPosition, scale);
    }

    //anchor
    for(int i = 1; i < entities.size(); i++) {
        const Entity& e{ entities.at(i) };
        fillRect(renderer, {e.hitbox.x - 2, e.hitbox.y - 2, 4, 4}, {255, 0, 0});
    }
}

const std::string& GameMap::getSheetName() {
    return textureSheet;
}

void GameMap::addGameObject(IDMapper idMaps, float depth, int texture, float x, float y) {
    static vec::vec2f offsetToMiddle{};

    std::string textures[1]{ 
        idMaps[texture]
     };

    if(entitiesLoaded == 0) {
        const Rect& bounds{ texture::getSpriteSheetBounds(textures[0]) };
        scale = 800.0 / bounds.h;
        std::cout << scale << " - scale calculated" << std::endl;
    }

    vec::vec2f pos{ x * scale, y * scale };

    //Get Random Hair texture
    bool isHair = (textures[0].find("anchor") != std::string::npos);
    if(isHair) {
        int hairCount = texture::getTextureCount("hair") / 2;
        int hairID = rnd::random(0, hairCount) + 1;

        textures[0] = textureSheet + "_hair_" + std::to_string(hairID);
    }

    Rect bounds{pos.x, pos.y, 0, 0};
    bounds.w = texture::getSpriteSheetBounds(textures[0]).w * scale;
    bounds.h = texture::getSpriteSheetBounds(textures[0]).h * scale;
    
    if(isHair) pos.x -= bounds.w / 2; 

    //Center Everything
    if(entitiesLoaded == 0) {
        entitiesLoaded++;
        offsetToMiddle = vec::vec2f{windowWidth, windowHeight} / 2 - vec::vec2f{bounds.w, bounds.h} / 2 - pos;
    }
    pos += offsetToMiddle;
    bounds.x += offsetToMiddle.x;
    bounds.y += offsetToMiddle.y;

    Sprite sprite{100, textures};
    if(!isHair) {
        textures[0] = textureSheet + "_face";

        std::vector<std::string> texturesList{};
        for(int i = 0; i < 20; i++) texturesList.push_back(textures[0] + "_0");
        for(int i = 1; i < texture::getTextureCount(textures[0]); i++) texturesList.push_back(textures[0] + "_" + std::to_string(i));

        sprite = Sprite{200, texturesList};
    }

    entities.push_back({ pos, sprite, bounds });
}

std::vector<Entity>& GameMap::getEntities() {
    return entities;
}