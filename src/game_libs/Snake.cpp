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

__attribute__((destructor)) void unload(void) {
    Log::info() << "Unloading Snake game..." << std::endl;
}

extern "C" std::unique_ptr<IGameModule> getGameModule(void) {
    Log::info() << "Entrypoint for Snake game" << std::endl;
    return std::make_unique<libs::game::Snake>();
}

libs::game::Snake::Snake() : isRunning(true),
    window(std::make_pair(198, 108), "Snake", "assets/snake/icon.png"),
    drawables(), sounds(), scores(), snakeLength(4), appleCount(0),
    direction(RIGHT), snakePosition(), applePosition({0, 0}) {
    initDrawablesMap();
    initDrawables();
    // initSounds();
    initScores();
}

libs::game::Snake::~Snake() {
}

bool libs::game::Snake::update(float deltaTime) {
    static float time = 0;

    time += deltaTime;
    if (time >= 1.0f) {
        time = 0;
        moveSnake();
        if (checkCollision() == false)
            return isRunning;
        updateDrawables();
    }
    return isRunning;
}

const Window &libs::game::Snake::getWindow(void) {
    return window;
}

const std::vector<std::unique_ptr<IDrawable>>
    &libs::game::Snake::getDrawables(void) {
    return drawables;
}

const std::vector<Sound> &libs::game::Snake::getSound(void) {
    return sounds;
}
