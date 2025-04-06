/*
** EPITECH PROJECT, 2025
** SDL2_event.cpp
** File description:
** SDL2_event.cpp
*/

#include <vector>

#include "./SDL2.hpp"

static void handleMouseButtonEvent(std::vector<SDL2::KeyEvent> &keyEvents,
                                   Uint32 type, SDL_MouseButtonEvent button) {
    SDL2::KeyEvent KeyEvent = {button.button, true, button.x, button.y, 0};

    if (type == SDL_MOUSEBUTTONDOWN) keyEvents.push_back(KeyEvent);
    if (type == SDL_MOUSEBUTTONUP) {
        KeyEvent.isPressed = false;
        keyEvents.push_back(KeyEvent);
    }
}

static void handleMouseMotionEvent(std::vector<SDL2::KeyEvent> &keyEvents,
                                   Uint32 type, SDL_MouseMotionEvent motion) {
    SDL2::KeyEvent KeyEvent = {motion.type, true, motion.x, motion.y, 0};

    if (type == SDL_MOUSEMOTION) keyEvents.push_back(KeyEvent);
}

static void handleMouseWheelEvent(std::vector<SDL2::KeyEvent> &keyEvents,
                                  Uint32 type, SDL_MouseWheelEvent wheel) {
    SDL2::KeyEvent KeyEvent = {wheel.type, true, wheel.x, wheel.y,
                               wheel.preciseY};

    if (type == SDL_MOUSEWHEEL) keyEvents.push_back(KeyEvent);
}

static void handleKeyEvent(std::vector<SDL2::KeyEvent> &keyEvents, Uint32 type,
                           SDL_Keycode key) {
    SDL2::KeyEvent keyEvent = {key, true, 0, 0, 0};

    if (type == SDL_KEYDOWN) keyEvents.push_back(keyEvent);
    if (type == SDL_KEYUP) {
        keyEvent.isPressed = false;
        keyEvents.push_back(keyEvent);
    }
}

void SDL2::pollEvent() {
    while (SDL_PollEvent(&event)) {
        handleMouseButtonEvent(keyEvents, event.type, event.button);
        handleMouseMotionEvent(keyEvents, event.type, event.motion);
        handleMouseWheelEvent(keyEvents, event.type, event.wheel);
        handleKeyEvent(keyEvents, event.type, event.key.keysym.sym);
    }
}

SDL2::KeyEvent SDL2::getKeyEvent() {
    SDL2::KeyEvent keyEvent = {-1, false, 0, 0, 0};

    if (keyEvents.empty()) return keyEvent;
    keyEvent = keyEvents.back();
    keyEvents.pop_back();
    return keyEvent;
}
