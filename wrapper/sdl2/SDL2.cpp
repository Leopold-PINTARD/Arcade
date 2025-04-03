/*
** EPITECH PROJECT, 2025
** SDL2.cpp
** File description:
** SDL2.cpp
*/

#include <SDL2/SDL_ttf.h>

#include "./SDL2.hpp"

SDL2::SDL2() : window(nullptr), renderer(nullptr), running(true),
    mouseEvent({0, 0, false, false, false}), keyEvents({}) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        getSDLError();
        exit(84);
    }
    if (TTF_Init() == -1) {
        getTTFError();
        exit(84);
    }
}

SDL2::~SDL2() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

bool SDL2::isRunning() {
    return running;
}

void SDL2::getSDLError() {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
        "%s\n",
        SDL_GetError());
}

void SDL2::getTTFError() {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
        "%s\n",
        TTF_GetError());
}
