/*
** EPITECH PROJECT, 2025
** SDL2_draw.cpp
** File description:
** SDL2_draw.cpp
*/

#include <SDL2/SDL_image.h>

#include <string>
#include <tuple>
#include <utility>

#include "./SDL2.hpp"

TTF_Font *SDL2::loadFont(const std::string &file) {
    TTF_Font *font = TTF_OpenFont(file.c_str(), 12);

    if (!font) {
        getSDLError();
        exit(84);
    }
    return font;
}

SDL_Color SDL2::getColor(std::tuple<int, int, int, int> color) {
    SDL_Color sdlColor;

    sdlColor.r = std::get<0>(color);
    sdlColor.g = std::get<1>(color);
    sdlColor.b = std::get<2>(color);
    sdlColor.a = std::get<3>(color);
    return sdlColor;
}

void SDL2::drawText(TTF_Font *font, const std::string text, SDL_Color color,
                    std::pair<float, float> scale, float rotation,
                    std::pair<int, int> pos) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {pos.first, pos.second,
                     static_cast<int>(surface->w * scale.first),
                     static_cast<int>(surface->h * scale.second)};
    SDL_Point center = {rect.w / 2, rect.h / 2};

    SDL_RenderCopyEx(renderer, texture, nullptr, &rect, rotation, &center,
                     SDL_FLIP_NONE);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void SDL2::drawSprite(const std::string &file, std::pair<float, float> scale,
                      float rotation, std::pair<int, int> pos) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, file.c_str());
    std::pair<int, int> textureSize;

    SDL_QueryTexture(texture, nullptr, nullptr, &textureSize.first,
                     &textureSize.second);
    SDL_Rect rect = {pos.first, pos.second,
                     static_cast<int>(textureSize.first * scale.first),
                     static_cast<int>(textureSize.second * scale.second)};
    SDL_Point center = {rect.w / 2, rect.h / 2};
    SDL_RenderCopyEx(renderer, texture, nullptr, &rect, rotation, &center,
                     SDL_FLIP_NONE);
    SDL_DestroyTexture(texture);
}
