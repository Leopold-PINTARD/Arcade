/*
** EPITECH PROJECT, 2025
** SDL2_event.cpp
** File description:
** SDL2_event.cpp
*/

#include <vector>

#include "./SDL2.hpp"

static void handleMouseButtonEvent(SDL2::MouseEvent &mouseEvent,
    Uint8 button, bool isDown) {
    if (button == SDL_BUTTON_LEFT)
        mouseEvent.leftButton = isDown;
    if (button == SDL_BUTTON_RIGHT)
        mouseEvent.rightButton = isDown;
    if (button == SDL_BUTTON_MIDDLE)
        mouseEvent.middleButton = isDown;
}

static void handleMouseEvent(SDL2::MouseEvent &mouseEvent,
    Uint32 type, Uint8 button, int x, int y) {
    if (type == SDL_MOUSEBUTTONDOWN)
        handleMouseButtonEvent(mouseEvent, button, true);
    if (type == SDL_MOUSEBUTTONUP)
        handleMouseButtonEvent(mouseEvent, button, false);
    if (type == SDL_MOUSEMOTION) {
        mouseEvent.x = x;
        mouseEvent.y = y;
    }
}

static void handleKeyEvent(std::vector<SDL2::KeyEvent> &keyEvents,
    Uint32 type, SDL_Keycode key) {
    SDL2::KeyEvent keyEvent;

    if (type == SDL_KEYDOWN) {
        keyEvent = {key, true};
        keyEvents.push_back(keyEvent);
    }
    if (type == SDL_KEYUP) {
        keyEvent = {key, false};
        keyEvents.push_back(keyEvent);
    }
}

void SDL2::pollEvent() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            running = false;
        handleMouseEvent(mouseEvent, event.type,
            event.button.button, event.button.x, event.button.y);
        handleKeyEvent(keyEvents, event.type,
            event.key.keysym.sym);
    }
}

SDL2::MouseEvent SDL2::getMouseEvent() {
    return mouseEvent;
}

SDL2::KeyEvent SDL2::getKeyEvent() {
    SDL2::KeyEvent keyEvent;

    if (keyEvents.empty())
        return {0, false};
    keyEvent = keyEvents.back();
    keyEvents.pop_back();
    return keyEvent;
}
