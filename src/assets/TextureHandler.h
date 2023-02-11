#ifndef TEXTUREHANDLER_H
#define TEXTUREHANDLER_H

#include "raylib.h"

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>´
#include <vector>

#include "../util/structs/structs.h"

namespace texture {
    void loadImagePng(const std::string& fileName, const std::string& internTextureName);
    void loadSpriteSheetPng(const std::string& fileName, const std::string& internSheetName);
    const Rect& getSpriteSheetBounds(const std::string& textureName);
    const Texture2D& getSpriteSheet(const std::string& textureName);

    void deleteAll();
    void deleteSheet(const std::string& sheetName);
    int getTextureCount(const std::string& substring = "");

    inline void loadSpriteSheetPng(const std::string& fileName) {
        loadSpriteSheetPng(fileName, fileName);
    }
}

#endif