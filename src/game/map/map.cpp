#include "map.h"

GameMap::GameMap(SDL_Renderer* renderer, int scale, const std::string& name) 
: scale(scale)
{

    if(name.length() > 0) loadMap(name, 
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

void GameMap::addGameObject(IDMapper idMaps, float depth, int texture, float x, float y) {
    int hairCount = (texture::getTextureCount() - 2)  / 2; //-1(face) -1 (anchor) / 2 (hair / outline)  
    int hairID = rnd::random(0, hairCount) + 1;

    vec::vec2f pos{ x * scale, y * scale };
    std::string textures[1]{ 
        idMaps[texture]
     };

    bool isHair = false;
    if(textures[0].find("anchor") != std::string::npos) {
        isHair = true;
        textures[0] = textureSheet + "_hair_" + std::to_string(hairID);
    }
    //std::cout << textures[0] << std::endl;

    Rect bounds{pos.x, pos.y, 0, 0};
    bounds.w = texture::getSpriteSheetBounds(textures[0]).w * scale;
    bounds.h = texture::getSpriteSheetBounds(textures[0]).h * scale;
    
    if(isHair) pos.x -= bounds.w / 2; 

    Sprite sprite{100, textures};
    entities.push_back({ pos, sprite, bounds });
}

std::vector<Entity>& GameMap::getEntities() {
    return entities;
}