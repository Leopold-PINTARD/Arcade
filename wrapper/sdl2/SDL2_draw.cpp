/*
** EPITECH PROJECT, 2025
** SDL2.cpp
** File description:
** SDL2.cpp
*/

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "./SDL2.hpp"

TTF_Font *SDL2::loadFont(const std::string &file, int size) {
    TTF_Font *font = TTF_OpenFont(file.c_str(), size);

    if (!font) {
        getSDLError();
        exit(84);
    }
    return font;
}

void SDL2::drawText(TTF_Font *font, const std::string text,
    SDL_Color color, int x, int y) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {x, y, surface->w, surface->h};

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
}

void SDL2::drawSprite(const std::string &file, int x, int y) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
    SDL_Rect rect = {x, y, 0, 0};

    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
}
