/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** main
*/

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <DataStructures/Sprite.hpp>
#include <modules/IDisplayModule.hpp>
#include <modules/IGameModule.hpp>

#include "./DLLoader.hpp"
#include "./log/Log.hpp"

static bool handleEvent(std::unique_ptr<IDisplayModule> &displayModule,
                        DLLoader<IDisplayModule> &gfxLoader,
                        std::unique_ptr<IGameModule> &gameModule,
                        DLLoader<IGameModule> &gameLoader) {
    Event currentEvent = displayModule->getEvent();

    gameModule->event(currentEvent);
    if (currentEvent.key == Key::KeyCode::NONE) return false;
    if (currentEvent.key == Key::KeyCode::SUPPR) std::exit(0);
    if (currentEvent.key == Key::KeyCode::KEY_1) {
        currentEvent.~Event();
        gfxLoader.switchLib("./lib/arcade_sdl2.so");
        if (gfxLoader.getInstance("getDisplayModule") == nullptr) std::exit(0);
        if (displayModule == nullptr) std::exit(0);
        displayModule->createWindow(gameModule->getWindow());
    }
    if (currentEvent.key == Key::KeyCode::KEY_2) {
        currentEvent.~Event();
        std::cout << "Switching to pacman" << std::endl;
        gameLoader.switchLib("./lib/arcade_pacman.so");
        if (gameLoader.getInstance("getGameModule") == nullptr) std::exit(0);
        if (gameModule == nullptr) std::exit(0);
        displayModule->createWindow(gameModule->getWindow());
    }
    return true;
}

int main() {
    DLLoader<IDisplayModule> gfxLoader("./lib/SFML.so");
    DLLoader<IGameModule> gameLoader("./lib/arcade_minesweeper.so");
    auto &displayModule = gfxLoader.getInstance("getDisplayModule");
    auto &gameModule = gameLoader.getInstance("getGameModule");
    Log logger("ERROR");
    auto previousTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();

    Log::setDebug(true);
    displayModule->createWindow(gameModule->getWindow());
    while (true) {
        currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - previousTime;
        previousTime = currentTime;

        displayModule->clear();
        while (handleEvent(displayModule, gfxLoader, gameModule, gameLoader)) {
        }
        for (Sound sound : gameModule->getSound())
            displayModule->handleSound(sound);
        for (const std::unique_ptr<IDrawable> &drawable :
             gameModule->getDrawables())
            displayModule->draw(*drawable);
        displayModule->display();
        gameModule->update(elapsedTime.count());
    }

    return 0;
}
