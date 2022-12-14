#ifndef ENTITY_H
#define ENTITY_H

#include "../../util/structs/vec2f.h"
#include "../../util/structs/structs.h"
#include "../../assets/sprite.h"

struct Entity {
    vec::vec2f position;
    Sprite sprite;
    Rect hitbox;
    vec::vec2f originPosition;
};

struct Request {
    std::string name;
    std::vector<Rect> hitboxes;
};

#endif