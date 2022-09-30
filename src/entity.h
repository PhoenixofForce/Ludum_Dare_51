#ifndef ENTITY_H
#define ENTITY_H

#include "data/vec2f.h"
#include "data/sprite.h"

struct Entity {
    vec::vec2f position;
    Sprite sprite;
};

#endif