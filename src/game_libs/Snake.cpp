/*
** EPITECH PROJECT, 2025
** Snake.cpp
** File description:
** Snake.cpp
*/

#include <memory>
#include <vector>
#include <string>
#include <utility>

#include "DataStructures/Window.hpp"
#include "DataStructures/Sprite.hpp"
#include "DataStructures/Sound.hpp"
#include "DataStructures/Event.hpp"
#include "DataStructures/Keys.hpp"

#include "src/game_libs/Snake.hpp"
#include "src/log/Log.hpp"

__attribute__((constructor)) void load(void) {
    Log::info() << "Loading Snake game..." << std::endl;
}
