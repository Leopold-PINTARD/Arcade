/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** main
*/

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <DataStructures/Sprite.hpp>
#include <modules/IDisplayModule.hpp>
#include <modules/IGameModule.hpp>

#include "./DLLoader.hpp"
#include "./log/Log.hpp"

static Sprite test() {
    Sprite sprite;
    sprite.setGUI_Textures({"/home/epi-jo/tek2/cpp/Arcade/assets/sprite.png"});
    sprite.setPosition(std::make_pair(0, 0));
    sprite.setScale(std::make_pair(100.0f, 100.0f));
    sprite.setRotation(0.0f);
    sprite.setAnimationTime(0.0f);
    sprite.setCurrentTexture(0);
    sprite.setGUI_Color(std::make_tuple(255, 255, 255, 255));
    sprite.setCLI_Color(
        std::make_pair(CLI_Color::CLI_WHITE, CLI_Color::CLI_WHITE));
    sprite.setCLI_Textures({"hello", "world"});
    return sprite;
}

static bool handleEvent(std::unique_ptr<IDisplayModule> &displayModule,
                        DLLoader<IDisplayModule> &gfxLoader) {
    Event currentEvent = displayModule->getEvent();

    // gameModule->event(*currentEvent);
    if (currentEvent.key == Key::KeyCode::NONE) return false;
    if (currentEvent.key == Key::KeyCode::SUPPR) std::exit(0);
    if (currentEvent.key == Key::KeyCode::KEY_N) {
        currentEvent.~Event();
        gfxLoader.switchLib("/home/epi-jo/tek2/cpp/Arcade/lib/SDL2.so");
        if (gfxLoader.getInstance("getDisplayModule") == nullptr) std::exit(0);
        if (displayModule == nullptr) std::exit(0);
        displayModule->createWindow(
            Window(std::make_pair(1920, 1080), "Arcade",
                   "/home/epi-jo/tek2/cpp/Arcade/assets/icon.png"));
    }
    return true;
}

int main() {
    DLLoader<IDisplayModule> gfxLoader(
        "/home/epi-jo/tek2/cpp/Arcade/lib/SDL2.so");
    // DLLoader<IGameModule> gameLoader("./lib/IGameModule.so");
    auto &displayModule = gfxLoader.getInstance("getDisplayModule");
    Sprite sprite = test();

    displayModule->createWindow(
        Window(std::make_pair(1920, 1080), "Arcade",
               "/home/epi-jo/tek2/cpp/Arcade/assets/icon.png"));
    while (true) {
        displayModule->clear();
        while (handleEvent(displayModule, gfxLoader)) {
        }
        // for (Sound sound : gameModule->getSound())
        //     displayModule->handleSound(sound);
        // for (const std::unique_ptr<IDrawable> &drawable :
        //      gameModule->getDrawables()) {
        //     displayModule->draw(*drawable);
        // }
        displayModule->draw(sprite);
        displayModule->display();
    }

    return 0;
}
