#ifndef RENDERING_H
#define RENDERING_H

#include <SDL2/SDL.h>
#include <string>

#include "assets/TextureHandler.h"
#include "util/structs/structs.h"
#include "util/structs/vec2f.h"

void fillRect(SDL_Renderer* renderer, const Rect& r, const Color& c);
void drawRect(SDL_Renderer* renderer, const Rect& r, const Color& c);

void drawImage(SDL_Renderer* renderer, const std::string& textureName, const vec::vec2f& position, int scale = 1);


#endif