#include <iostream>
#include <cstring>
#include <SDL2/SDL.h>
#include "globals.hpp"
#include "renderer.hpp"

SDL_Window* window;
SDL_Renderer* screenRenderer;
SDL_Texture* screenTexture;
u8* screenData;

void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL Init Error: " << SDL_GetError();
    }
    window = SDL_CreateWindow("3D Stuff", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, XResolution, YResolution, SDL_WINDOW_SHOWN);
    if(window == NULL) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError();
    }
    screenRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (screenRenderer == NULL) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError();
    }
    screenTexture = SDL_CreateTexture(screenRenderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, XResolution, YResolution);
}

int main(int argc, char** argv) {
    initSDL();
    screenData = new u8[XResolution * YResolution * 3];

    SDL_Event event;
    while (true) {
        while(SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                delete[] screenData;
                SDL_DestroyTexture(screenTexture);
                SDL_DestroyRenderer(screenRenderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;
            }
        }

        std::memset(screenData, 0, XResolution * YResolution * 3); // clear screen
        renderFrame(screenData);
        SDL_UpdateTexture(screenTexture, NULL, screenData, XResolution * 3);
        SDL_RenderCopy(screenRenderer, screenTexture, NULL, NULL);
        SDL_RenderPresent(screenRenderer);
    }
}
