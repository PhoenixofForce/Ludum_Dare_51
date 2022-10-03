#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "../util/structs/structs.h"

namespace texture {
    void loadImagePng(SDL_Renderer* renderer, const std::string& fileName, const std::string& internTextureName);
    void loadSpriteSheetPng(SDL_Renderer* renderer, const std::string& fileName, const std::string& internSheetName);
    const Rect& getSpriteSheetBounds(const std::string& textureName);
    SDL_Texture* getSpriteSheet(const std::string& textureName);

    void deleteAll();
    void deleteSheet(const std::string& sheetName);
    int getTextureCount(const std::string& substring = "");

    inline void loadSpriteSheetPng(SDL_Renderer* renderer, const std::string& fileName) {
        loadSpriteSheetPng(renderer, fileName, fileName);
    }
}

#endif