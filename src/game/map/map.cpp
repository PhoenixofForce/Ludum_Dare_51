#include "map.h"

GameMap::GameMap(SDL_Renderer* renderer, int inWindowWidth, int inWindowHeight, int inScale, const std::string& name) 
: scale(inScale), windowWidth(inWindowWidth), windowHeight(inWindowHeight)
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
    std::string textures[1]{ 
        idMaps[texture]
     };

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
    static int entityID = 0;
    static vec::vec2f offsetToMiddle{};
    if(entityID == 0) {
        entityID++;
        offsetToMiddle = vec::vec2f{windowWidth, windowHeight} / 2 - vec::vec2f{bounds.w, bounds.h} / 2 - pos;
    }
    pos += offsetToMiddle;
    bounds.x += offsetToMiddle.x;
    bounds.y += offsetToMiddle.y;

    Sprite sprite{100, textures};
    if(!isHair) {
        textures[0] = textureSheet + "_face";
        sprite = Sprite{100, textures[0], texture::getTextureCount(textures[0])};
    }

    entities.push_back({ pos, sprite, bounds });
}

std::vector<Entity>& GameMap::getEntities() {
    return entities;
}