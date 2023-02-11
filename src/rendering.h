#ifndef RENDERING_H
#define RENDERING_H

#include <string>

#include "raylib.h"
#include "assets/TextureHandler.h"
#include "util/structs/structs.h"
#include "util/structs/vec2f.h"

void fillRect(const Rect& r, const Color_c& c);
void fillRect(const Rect& r, const Color& c);
void drawRect(const Rect& r, const Color_c& c);

void drawImage(const std::string& textureName, const vec::vec2f& position, float scale = 1);


#endif