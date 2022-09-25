#ifndef SPRITE_H
#define SPRITE_H

#include <vector>
#include <string>

#include "../util/time.h"

class Sprite {

public:

    template<size_t N>
    Sprite(int time, const std::string (&sprites)[N]);
    Sprite(int time, const std::string& spriteName, int count);

    const std::string& getTexture(long start, long current);

    const std::string& getTexture(long start);

    const std::string& getTexture();

private:
    int time;
    std::vector<std::string> spriteList{};

};


#endif