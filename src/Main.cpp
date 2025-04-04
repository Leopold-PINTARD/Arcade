/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** main
*/

#include <memory>
#include <string>
#include <utility>

#include <DataStructures/Sprite.hpp>
#include <modules/IDisplayModule.hpp>
#include <modules/IGameModule.hpp>

#include "./DLLoader.hpp"

static Sprite test() {
    Sprite sprite;
    sprite.setGUI_Textures({"./assets/sprite.png"});
    sprite.setPosition(std::make_pair(0, 0));
    sprite.setScale(std::make_pair(1.0f, 1.0f));
    sprite.setRotation(0.0f);
    sprite.setAnimationTime(0.0f);
    sprite.setCurrentTexture(0);
    sprite.setGUI_Color(std::make_tuple(255, 255, 255, 255));
    return sprite;
}

int main() {
    DLLoader<IDisplayModule> gfxLoader("./lib/SFML.so");
    // DLLoader<IGameModule> gameLoader("./lib/IGameModule.so");
    std::unique_ptr<IDisplayModule> &displayModule =
        gfxLoader.getInstance("getDisplayModule");
    // std::unique_ptr<IGameModule> &gameModule =
    //     gameLoader.getInstance("getGameModule");
    Sprite sprite = test();
    std::unique_ptr<Event> currentEvent = nullptr;

    displayModule->createWindow(
        Window(std::make_pair(1920, 1080), "Arcade", "./assets/icon.png"));
    while (true) {
        displayModule->clear();
        currentEvent = std::make_unique<Event>(displayModule->getEvent());
        while (currentEvent->key != Key::KeyCode::NONE) {
            // gameModule->event(*currentEvent);
            if (currentEvent->key == Key::KeyCode::SUPPR) return 0;
            currentEvent.reset(nullptr);
            currentEvent = std::make_unique<Event>(displayModule->getEvent());
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
