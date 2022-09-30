#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <string>

#include "../util/time.h"

class Sprite {

public:

    template<size_t N>
    Sprite(int time, const std::string (&sprites)[N]) {
        this->time = time;
        for(int i = 0; i < N; i++) {
            spriteList.push_back(sprites[i]);
        }
    }
    Sprite(int time, const std::string& spriteName, int count);

    const std::string& getTexture(long start, long current) const;

    const std::string& getTexture(long start) const;

    const std::string& getTexture() const;

private:
    int time;
    std::vector<std::string> spriteList{};

};


#endif