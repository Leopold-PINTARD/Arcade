/*
** EPITECH PROJECT, 2025
** SnakeInit.cpp
** File description:
** SnakeInit.cpp
*/

#include <string>
#include <memory>
#include <utility>

#include "DataStructures/Sprite.hpp"
#include "DataStructures/Sound.hpp"

#include "src/game_libs/Snake.hpp"

static Sprite createSprite(const std::string path, const std::string text) {
    Sprite sprite;
    sprite.setGUI_Textures({path});
    sprite.setCLI_Textures({text});
    return sprite;
}

void libs::game::Snake::initDrawablesMap(void) {
    drawablesMap["snake"] = std::make_unique<Sprite>(
        createSprite("assets/snake/body_horizontal.png", "o "));
    drawablesMap["apple"] = std::make_unique<Sprite>(
        createSprite("assets/snake/apple.png", "a "));
    drawablesMap["light_green"] = std::make_unique<Sprite>(
        createSprite("assets/snake/light_green.png", "# "));
    drawablesMap["dark_green"] = std::make_unique<Sprite>(
        createSprite("assets/snake/dark_green.png", "# "));
}

void libs::game::Snake::initDrawables(void) {
    bool isDarkGreen = true;

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (isDarkGreen) {
                auto darkGreen = std::make_unique<Sprite>();
                *darkGreen = *static_cast<Sprite *>(
                    drawablesMap["dark_green"].get());
                darkGreen->setPosition({i, j});
                drawables.push_back(std::move(darkGreen));
            } else {
                auto lightGreen = std::make_unique<Sprite>();
                *lightGreen = *static_cast<Sprite *>(
                    drawablesMap["light_green"].get());
                lightGreen->setPosition({i, j});
                drawables.push_back(std::move(lightGreen));
            }
            isDarkGreen = !isDarkGreen;
        }
        isDarkGreen = !isDarkGreen;
    }
    for (int k = 0; k < 4; k++) {
        auto snakePart = std::make_unique<Sprite>();
        *snakePart = *static_cast<Sprite *>(drawablesMap["snake"].get());
        snakePart->setPosition({12 - k, 9});
        drawables.push_back(std::move(snakePart));
        snakePosition.push_back({12 - k, 9});
    }
    auto apple = std::make_unique<Sprite>();
    *apple = *static_cast<Sprite *>(drawablesMap["apple"].get());
    applePosition = {rand() % 20, rand() % 20};
    apple->setPosition(applePosition);
    drawables.push_back(std::move(apple));
}
