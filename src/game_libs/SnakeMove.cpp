/*
** EPITECH PROJECT, 2025
** Snake.cpp
** File description:
** Snake.cpp
*/

#include <utility>
#include <memory>

#include "DataStructures/Sprite.hpp"

#include "src/game_libs/Snake.hpp"

void libs::game::Snake::moveSnake(void) {
    std::pair<int, int> newHead = snakePosition.front();

    switch (direction) {
        case UP:
            newHead.second--;
            break;
        case DOWN:
            newHead.second++;
            break;
        case LEFT:
            newHead.first--;
            break;
        case RIGHT:
            newHead.first++;
            break;
    }
    if (newHead == applePosition) {
        appleCount++;
        applePosition = {rand() % 20, rand() % 20};
    } else {
        snakePosition.pop_back();
    }
    snakePosition.insert(snakePosition.begin(), newHead);
}

bool libs::game::Snake::checkCollision(void) {
    for (size_t i = 1; i < snakePosition.size(); ++i) {
        if (snakePosition[i] == snakePosition.front()) {
            isRunning = false;
            return isRunning;
        }
    }
    if (snakePosition.front().first < 0 || snakePosition.front().first >= 20 ||
        snakePosition.front().second < 0 || snakePosition.front().second >= 20)
        isRunning = false;
    return isRunning;
}

void libs::game::Snake::updateDrawables(void) {
    drawables.erase(drawables.begin() + 400, drawables.end());
    for (const auto &pos : snakePosition) {
        auto snakePart = std::make_unique<Sprite>();
        *snakePart = *static_cast<Sprite *>(drawablesMap["snake"].get());
        snakePart->setPosition(pos);
        drawables.push_back(std::move(snakePart));
    }
    auto apple = std::make_unique<Sprite>();
    *apple = *static_cast<Sprite *>(drawablesMap["apple"].get());
    apple->setPosition(applePosition);
    drawables.push_back(std::move(apple));
}
