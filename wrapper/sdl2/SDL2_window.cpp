/*
** EPITECH PROJECT, 2025
** SDL2.cpp
** File description:
** SDL2.cpp
*/

#include <SDL2/SDL_image.h>
#include <string>

#include "./SDL2.hpp"

static bool setWindowIcon(SDL_Window *window, const std::string &iconPath) {
    SDL_Surface *icon = IMG_Load(iconPath.c_str());

    if (!icon)
        return false;
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);
    return true;
}

void SDL2::createWindow(const std::string &title,
    const std::string &iconPath, int width, int height) {
    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        0);
    if (!window) {
        getSDLError();
        exit(84);
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer || !setWindowIcon(window, iconPath)) {
        getSDLError();
        exit(84);
    }
}

void SDL2::clearWindow() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void SDL2::displayWindow() {
    SDL_RenderPresent(renderer);
}
