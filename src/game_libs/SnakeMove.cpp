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
