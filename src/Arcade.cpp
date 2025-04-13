/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Arcade
*/

#include "Arcade.hpp"

#include <algorithm>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

#include <DataStructures/Text.hpp>

#include "./log/Log.hpp"

static Window menuWindow = {{32, 32}, "Arcade", "./assets/icon.png"};

Arcade::Arcade(std::string gfxLib)
    : _previousTime(std::chrono::high_resolution_clock::now()),
      _currentTime(std::chrono::high_resolution_clock::now()),
      _inMenu(true),
      _gfxLoader(gfxLib),
      _gameLoader(),
      _displayModule(_gfxLoader.getInstance("getDisplayModule")),
      _gameModule(_gameLoader.getInstance("getGameModule")),
      _currentGfxLib(gfxLib),
      _currentGameLib("") {}

Arcade::~Arcade() {}

void Arcade::cycleCurrentGfxLib() {
    auto it = std::find(_gfxModules.begin(), _gfxModules.end(), _currentGfxLib);
    if (it != _gfxModules.end() && ++it != _gfxModules.end())
        _currentGfxLib = *it;
    else
        _currentGfxLib = _gfxModules.front();
}

bool Arcade::eventStatusIs(Event::KeyStatus status, Event currentEvent) {
    try {
        if (std::any_cast<Event::KeyStatus>(currentEvent.value) == status)
            return true;
        return false;
    } catch (const std::bad_any_cast &e) {
        return false;
    }
}

void Arcade::switchGfxLib(std::string path, const Window &window) {
    _gfxLoader.switchLib(path);
    if (_gfxLoader.getInstance("getDisplayModule") == nullptr) std::exit(84);
    if (_displayModule == nullptr) std::exit(84);
    _displayModule->createWindow(window);
}

void Arcade::switchGameLib(std::string path) {
    _gameLoader.switchLib(path);
    if (_gameLoader.getInstance("getGameModule") == nullptr) std::exit(84);
    if (_displayModule == nullptr) std::exit(84);
    switchGfxLib(_currentGfxLib, _gameModule->getWindow());
}

void Arcade::cycleCurrentGameLib() {
    auto it =
        std::find(_gameModules.begin(), _gameModules.end(), _currentGameLib);
    if (it != _gameModules.end() && ++it != _gameModules.end())
        _currentGameLib = *it;
    else
        _currentGameLib = _gameModules.front();
}

bool Arcade::handleMenuEvent() {
    Event currentEvent = _displayModule->getEvent();

    if (currentEvent.key == Key::KeyCode::NONE) return false;
    if (currentEvent.key == Key::KeyCode::ECHAP) std::exit(0);
    if (currentEvent.key == Key::KeyCode::KEY_1) {
        if (!eventStatusIs(Event::KeyStatus::KEY_PRESSED, currentEvent))
            return true;
        cycleCurrentGfxLib();
    }
    if (currentEvent.key == Key::KeyCode::KEY_2) {
        if (!eventStatusIs(Event::KeyStatus::KEY_PRESSED, currentEvent))
            return true;
        cycleCurrentGameLib();
    }
    if (currentEvent.key == Key::KeyCode::TAB) {
        if (!eventStatusIs(Event::KeyStatus::KEY_PRESSED, currentEvent))
            return true;
        currentEvent.~Event();
        switchGameLib(_currentGameLib);
        _inMenu = false;
        return false;
    }
    if (currentEvent.key == Key::KeyCode::KEY_3) {
        if (!eventStatusIs(Event::KeyStatus::KEY_PRESSED, currentEvent))
            return true;
        currentEvent.~Event();
        switchGfxLib(_currentGfxLib, menuWindow);
        return false;
    }
    return true;
}

bool Arcade::handleGameEvent() {
    Event currentEvent = _displayModule->getEvent();

    _gameModule->event(currentEvent);
    if (currentEvent.key == Key::KeyCode::NONE) return false;
    if (currentEvent.key == Key::KeyCode::ECHAP) std::exit(0);
    if (currentEvent.key == Key::KeyCode::KEY_1) {
        if (!eventStatusIs(Event::KeyStatus::KEY_PRESSED, currentEvent))
            return true;
        currentEvent.~Event();
        cycleCurrentGfxLib();
        switchGfxLib(_currentGfxLib, _gameModule->getWindow());
        return false;
    }
    if (currentEvent.key == Key::KeyCode::KEY_2 ||
        currentEvent.key == Key::KeyCode::KEY_3) {
        if (!eventStatusIs(Event::KeyStatus::KEY_PRESSED, currentEvent))
            return true;
        if (currentEvent.key == Key::KeyCode::KEY_2) cycleCurrentGameLib();
        currentEvent.~Event();
        switchGameLib(_currentGameLib);
        return false;
    }
    if (currentEvent.key == Key::KeyCode::TAB) {
        if (!eventStatusIs(Event::KeyStatus::KEY_PRESSED, currentEvent))
            return true;
        currentEvent.~Event();
        _gameLoader.unload();
        switchGfxLib(_currentGfxLib, menuWindow);
        _inMenu = true;
        return false;
    }
    return true;
}

void Arcade::run() {
    updateLibLists("./lib/");
    Log::setDebug(false);
    if (!_inMenu)
        _displayModule->createWindow(_gameModule->getWindow());
    else
        _displayModule->createWindow(menuWindow);
    while (true) {
        if (_inMenu)
            menuLoop();
        else
            gameLoop();
    }
}

void Arcade::gameLoop() {
    _currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsedTime = _currentTime - _previousTime;
    _previousTime = _currentTime;

    _displayModule->clear();
    while (handleGameEvent()) {
    }
    if (_inMenu) return;
    for (const std::unique_ptr<IDrawable> &drawable :
         _gameModule->getDrawables())
        _displayModule->draw(*drawable);
    for (Sound sound : _gameModule->getSound())
        _displayModule->handleSound(sound);
    _displayModule->display();
    _gameModule->update(elapsedTime.count());
}

void Arcade::menuLoop() {
    _currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsedTime = _currentTime - _previousTime;
    _previousTime = _currentTime;

    _displayModule->clear();
    while (handleMenuEvent()) {
    }
    int i = 0;
    Text infoText;
    infoText.setStr("Graphic Libraries");
    infoText.setGUI_Color({255, 255, 255, 255});
    infoText.setCLI_Color({CLI_Color::CLI_WHITE, CLI_Color::CLI_BLACK});
    infoText.setPosition({0, 0});
    infoText.setFontPath("./assets/fonts/NotoSans.ttf");
    infoText.setScale({10, 10});
    _displayModule->draw(infoText);
    for (auto lib : _gfxModules) {
        Text text;
        if (lib == _currentGfxLib)
            text.setStr("> " + lib);
        else
            text.setStr("- " + lib);
        text.setGUI_Color({255, 255, 255, 255});
        text.setCLI_Color({CLI_Color::CLI_WHITE, CLI_Color::CLI_BLACK});
        text.setPosition({0, i + 1});
        text.setFontPath("./assets/fonts/NotoSans.ttf");
        text.setScale({10, 10});
        _displayModule->draw(text);
        i++;
    }
    infoText.setStr("Game Libraries");
    infoText.setPosition({0, i + 2});
    _displayModule->draw(infoText);
    for (auto lib : _gameModules) {
        Text text;
        if (lib == _currentGameLib)
            text.setStr("> " + lib);
        else
            text.setStr("- " + lib);
        text.setGUI_Color({255, 255, 255, 255});
        text.setCLI_Color({CLI_Color::CLI_WHITE, CLI_Color::CLI_BLACK});
        text.setPosition({0, i + 3});
        text.setFontPath("./assets/fonts/NotoSans.ttf");
        text.setScale({10, 10});
        _displayModule->draw(text);
        i++;
    }
    _displayModule->display();
}

void Arcade::updateLibLists(std::string path) {
    std::filesystem::path dirPath(path);

    if (!std::filesystem::exists(dirPath) ||
        !std::filesystem::is_directory(dirPath)) {
        Log::error() << "Error opening directory: " << path << std::endl;
        return;
    }

    for (const auto &entry : std::filesystem::directory_iterator(dirPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".so") {
            try {
                DLLoader<IDisplayModule> gfxLoader(
                    entry.path().relative_path().string());
                if (gfxLoader.entrypointExists("getDisplayModule") == true) {
                    _gfxModules.push_back(
                        entry.path().relative_path().string());
                    continue;
                }
            } catch (const DLLoader<IDisplayModule>::DLLoaderException &e) {
                std::cout << "Not gfx: " << e.what() << std::endl;
            }
            try {
                DLLoader<IGameModule> gameLoader(
                    entry.path().relative_path().string());
                if (gameLoader.entrypointExists("getGameModule") == false)
                    continue;
                _gameModules.push_back(entry.path().relative_path().string());
            } catch (const DLLoader<IGameModule>::DLLoaderException &e) {
                std::cout << "Not game: " << e.what() << std::endl;
            }
        }
    }
    _currentGameLib = _gameModules.front();
}
