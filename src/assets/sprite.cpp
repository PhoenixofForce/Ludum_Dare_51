#include "sprite.h"

#include <iostream>

Sprite::Sprite(int time, const std::string& spriteName, int count) {
    this->time = time;
    for(int i = 0; i < count; i++) {
        spriteList.push_back(spriteName + "_" + std::to_string(i));
    }
}

Sprite::Sprite(int time, std::vector<std::string> textures) {
    this-> time = time;
    spriteList = textures;
}


const std::string& Sprite::getTexture(long start, long current) const {
    return spriteList.at(((int) ((current-start) / time)) % spriteList.size());
}

const std::string& Sprite::getTexture(long start) const {
    return getTexture(start, clck::getCurrentTime());
}

const std::string& Sprite::getTexture() const {
    return getTexture(start);
}

void Sprite::reset() {
    start = clck::getCurrentTime();
}