#include <iostream>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <windows.h>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <string>

#include "game/game.h"
#include "util/time.h"

int WIDTH = 1080, HEIGHT = 720;
const std::string title = "Speed Barber";
bool isFullscreen = true;

void getFPS(long& fps, long& dt, long& lastUp);
bool handleEvents(SDL_Window* window, Game& game, std::map<int, bool>& pressedKeys);

int main(int argc, char* argv[]) {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    std::cout.precision(17);

    SDL_Init(SDL_INIT_EVERYTHING);
    Mix_Init(0);
    
    //Create Window
    SDL_Window* window {
        SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 
            SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE | (isFullscreen? SDL_WINDOW_FULLSCREEN_DESKTOP: 0)
        )
    };
    SDL_Surface* tmpSurface{ IMG_Load("res/cutter.png") };
    SDL_SetWindowIcon(window, tmpSurface);
    SDL_SetWindowMinimumSize(window, 800, 600);

    if(window == NULL) {
        std::cout << "Window couldnt be created: " << SDL_GetError() << std::endl;
        return 1;
    }

    //Init Music and Audio
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_VolumeMusic(45);

    SDL_Renderer* renderer{SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)};

    //Init game related objects
    Game game{ renderer, WIDTH, HEIGHT };
    std::map<int, bool> pressedKeys{};

    while(true) {
        long fps, dt, lastUpdate;
        getFPS(fps, dt, lastUpdate);

        std::string newTitle{title + " (" + std::to_string(fps) + ")"};
        SDL_SetWindowTitle(window, newTitle.c_str());

        bool quit = handleEvents(window, game, pressedKeys);
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

void getFPS(long& fps, long& dt, long& lastUp) {
    static long lastUpdate = clck::getCurrentTime();
    static long lastUpdateNano = clck::getCurrentTimeNS();

    dt = clck::getCurrentTime() - lastUpdate;
    long dtNano = clck::getCurrentTimeNS() - lastUpdateNano;
    lastUpdate = clck::getCurrentTime();
    lastUpdateNano = clck::getCurrentTimeNS();

    fps = dtNano != 0? 1000000000 / dtNano: 0;
    lastUp = lastUpdate;
}

bool handleEvents(SDL_Window* window, Game& game, std::map<int, bool>& pressedKeys) {
    bool quit = false;
    SDL_Event event;

    while(SDL_PollEvent((&event))) {
        if(event.type == SDL_QUIT) {
            quit = true;
            break;
        }

        if(event.type == SDL_WINDOWEVENT) {
            if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
                int nx = event.window.data1;
                int ny = event.window.data2;
                
                WIDTH = nx;
                HEIGHT = ny;

                game.handleResize(WIDTH, HEIGHT);
            }
        }

        if(event.type == SDL_KEYUP) {
            int key = event.key.keysym.sym;
            pressedKeys[key] = false;

            if(key == SDLK_RETURN && (pressedKeys[SDLK_LALT] || pressedKeys[SDLK_RALT])) {
                isFullscreen = !isFullscreen;
                SDL_SetWindowFullscreen(window, isFullscreen? SDL_WINDOW_FULLSCREEN_DESKTOP: 0);

                if(!isFullscreen) {
                    SDL_GetWindowSize(window, &WIDTH, &HEIGHT);
                    game.handleResize(WIDTH, HEIGHT);
                }
            }
        }

        if(event.type == SDL_KEYDOWN) {
            int key = event.key.keysym.sym;
            pressedKeys[key] = true;
        }

        if(event.type == SDL_MOUSEMOTION) {
            int windowX, windowY;
            SDL_GetWindowPosition(window, &windowX, &windowY);

            int xMouse, yMouse;
            SDL_GetGlobalMouseState(&xMouse,&yMouse);
            xMouse -= windowX;
            yMouse -= windowY;

            game.setMouse(xMouse, yMouse);
        }

        if(event.type == SDL_MOUSEBUTTONDOWN) {
            if(event.button.button == SDL_BUTTON_LEFT) pressedKeys[-101] = true;
        }

        if(event.type == SDL_MOUSEBUTTONUP) {
            if(event.button.button == SDL_BUTTON_LEFT) pressedKeys[-101] = false;
        }
    }

    return quit;
}