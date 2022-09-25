#include "sprite.h"

template<size_t N>
Sprite::Sprite(int time, const std::string (&sprites)[N]) {
    this->time = time;
    for(int i = 0; i < N; i++) {
        spriteList.push_back(sprites[i]);
    }
}

Sprite::Sprite(int time, const std::string& spriteName, int count) {
    this->time = time;
    for(int i = 0; i < count; i++) {
        spriteList.push_back(spriteName + "_" + std::to_string(i));
    }
}

const std::string& Sprite::getTexture(long start, long current) {
    return spriteList.at(((int) ((current-start) / time)) % spriteList.size());
}

const std::string& Sprite::getTexture(long start) {
    return getTexture(start, clck::getCurrentTime());
}

const std::string& Sprite::getTexture() {
    return getTexture(0);
}