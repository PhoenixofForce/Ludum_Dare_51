#include "rendering.h"

void fillRect(const Rect& r, const Color_c& c) {
    fillRect(r, Color{(unsigned char)c.r, (unsigned char) c.g, (unsigned char)c.b});
}

void fillRect(const Rect& r, const Color& c) {
    DrawRectangle(r.x, r.y, r.w, r.h, c);
}

void drawRect(const Rect& r, const Color_c& c) {
    DrawRectangleLines(r.x, r.y, r.w, r.h, {(unsigned char)c.r, (unsigned char) c.g, (unsigned char)c.b, 255});
}

void drawImage(const std::string& textureName, const vec::vec2f& position, float scale) {
    const Texture2D& texture{ texture::getSpriteSheet(textureName) };
    const Rect& source{ texture::getSpriteSheetBounds(textureName) };

    DrawTexturePro(
        texture, 
        {source.x * 1.0f, source.y * 1.0f, source.w * 1.0f, source.h * 1.0f }, 
        {position.x, position.y, source.w * scale, source.h * scale}, 
        {0, 0}, 
        0, 
        WHITE
    ); 

    /*   
    SDL_Rect from{ source.x, source.y, source.w, source.h };
    SDL_Rect to{ position.xi(), position.yi(), source.w * scale, source.h * scale };

    SDL_RenderCopy(renderer, texture, &from, &to);
    */
}