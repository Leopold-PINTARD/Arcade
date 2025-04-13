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
