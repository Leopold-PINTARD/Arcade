/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Arcade
*/

#include "Arcade.hpp"

#include <chrono>
#include <iostream>
#include <memory>
#include <string>

#include "./log/Log.hpp"

Arcade::Arcade(std::string gfxLib)
    : _gfxLoader(gfxLib),
      _gameLoader("./lib/arcade_minesweeper.so"),
      _displayModule(_gfxLoader.getInstance("getDisplayModule")),
      _gameModule(_gameLoader.getInstance("getGameModule")) {}

Arcade::~Arcade() {}

bool Arcade::handleEvent() {
    Event currentEvent = _displayModule->getEvent();

    _gameModule->event(currentEvent);
    if (currentEvent.key == Key::KeyCode::NONE) return false;
    if (currentEvent.key == Key::KeyCode::SUPPR) std::exit(0);
    if (currentEvent.key == Key::KeyCode::KEY_1) {
        try {
            std::any_cast<Event::KeyStatus>(currentEvent.value);
        } catch (const std::bad_any_cast &e) {
            return true;
        }
        currentEvent.~Event();
        _gfxLoader.switchLib("./lib/arcade_sfml.so");
        if (_gfxLoader.getInstance("getDisplayModule") == nullptr)
            std::exit(84);
        if (_displayModule == nullptr) std::exit(84);
        _displayModule->createWindow(_gameModule->getWindow());
    }
    if (currentEvent.key == Key::KeyCode::KEY_2) {
        currentEvent.~Event();
        std::cout << "Switching to pacman" << std::endl;
        _gameLoader.switchLib("./lib/arcade_pacman.so");
        if (_gameLoader.getInstance("getGameModule") == nullptr) std::exit(84);
        if (_gameModule == nullptr) std::exit(84);
        _displayModule->createWindow(_gameModule->getWindow());
    }
    return true;
}

void Arcade::run() {
    auto previousTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();

    Log::setDebug(false);
    _displayModule->createWindow(_gameModule->getWindow());
    while (true) {
        currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - previousTime;
        previousTime = currentTime;

        _displayModule->clear();
        while (handleEvent()) {
        }
        for (const std::unique_ptr<IDrawable> &drawable :
             _gameModule->getDrawables())
            _displayModule->draw(*drawable);
        for (Sound sound : _gameModule->getSound())
            _displayModule->handleSound(sound);
        _displayModule->display();
        _gameModule->update(elapsedTime.count());
    }
}
