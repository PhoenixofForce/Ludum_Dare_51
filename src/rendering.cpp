#include "rendering.h"

void fillRect(SDL_Renderer* renderer, const Rect& r, const Color& c) {
    SDL_Rect rect{r.x, r.y, r.w, r.h};

    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderFillRect(renderer, &rect);
}

void drawRect(SDL_Renderer* renderer, const Rect& r, const Color& c) {
    SDL_Rect rect{r.x, r.y, r.w, r.h};

    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderDrawRect(renderer, &rect);
}

void drawImage(SDL_Renderer* renderer, const std::string& textureName, const vec::vec2f& position, float scale) {
    SDL_Texture* texture{ texture::getSpriteSheet(textureName) };
    const Rect& source{ texture::getSpriteSheetBounds(textureName) };

    SDL_Rect from{ source.x, source.y, source.w, source.h };
    SDL_Rect to{ position.xi(), position.yi(), source.w * scale, source.h * scale };

    SDL_RenderCopy(renderer, texture, &from, &to);
}