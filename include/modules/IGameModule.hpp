/*
** EPITECH PROJECT, 2025
** Arcade-Headers
** File description:
** IGameModule
*/

#pragma once
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <DataStructures/Event.hpp>
#include <DataStructures/IDrawable.hpp>
#include <DataStructures/Sound.hpp>
#include <DataStructures/Window.hpp>

class IGameModule {
 public:
    virtual bool update(float deltaTime) = 0;
    virtual const Window &getWindow(void) = 0;
    virtual const std::vector<std::unique_ptr<IDrawable>> &getDrawables(
        void) = 0;
    virtual const std::vector<Sound> &getSound(void) = 0;
    virtual bool event(const Event &events) = 0;
    virtual std::vector<std::pair<std::string, int>> getScores(void) = 0;
};

// extern "C" std::unique_ptr<IGameModule> getGameModule();
