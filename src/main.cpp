#include <iostream>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include <string>

#include "game/game.h"
#include "util/time.h"

const int WIDTH = 800, HEIGHT = 600;
const std::string title = "Hello Window";

int main(int argc, char* argv[]) {
    std::cout.precision(17);

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window {
        SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI)
    };

    if(window == NULL) {
        std::cout << "Window couldnt be created: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* renderer{SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)};
    SDL_Event event;

    Game game{ renderer, WIDTH, HEIGHT };
    std::map<int, bool> pressedKeys{};

    while(true) {
        static long lastUpdate = clck::getCurrentTime();
        static long lastUpdateNano = clck::getCurrentTimeNS();

        long dt = clck::getCurrentTime() - lastUpdate;
        long dtNano = clck::getCurrentTimeNS() - lastUpdateNano;
        lastUpdate = clck::getCurrentTime();
        lastUpdateNano = clck::getCurrentTimeNS();

        long fps = dtNano != 0? 1000000000 / dtNano: 0;

        std::string newTitle{title + " (" + std::to_string(fps) + ")"};
        SDL_SetWindowTitle(window, newTitle.c_str());

        bool quit = false;
        while(SDL_PollEvent((&event))) {
            if(event.type == SDL_QUIT) {
                quit = true;
                break;
            }

            if(event.type == SDL_KEYUP) {
                int key = event.key.keysym.sym;
                pressedKeys[key] = false;
            }

            if(event.type == SDL_KEYDOWN) {
                int key = event.key.keysym.sym;
                pressedKeys[key] = true;
            }
        }
        if(quit) break;

        game.update(dt, pressedKeys);
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        game.render(renderer);

        SDL_RenderPresent(renderer);

        clck::sleep(lastUpdate + (1000/60) - clck::getCurrentTime());
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}