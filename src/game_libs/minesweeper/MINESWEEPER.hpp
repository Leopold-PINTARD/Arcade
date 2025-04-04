/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** MINESWEEPER
*/

#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "modules/IGameModule.hpp"
#include "minesweeper/Grid.hpp"

class MINESWEEPER : public IGameModule {
 public:
    MINESWEEPER();
    ~MINESWEEPER();

    bool update(float deltaTime);
    const Window &getWindow(void);
    const std::vector<std::unique_ptr<IDrawable>> &getDrawables(void);
    const std::vector<Sound> &getSound(void);
    bool event(const Event &events);
    std::vector<std::pair<std::string, int>> getScores(void);

 private:
    std::vector<std::unique_ptr<IDrawable>> _drawables;
    std::vector<Sound> _sounds;
    Window _window;
    bool _gameRunning;
    bool _gameOver;
    bool _won;
    int _offsetX;
    int _offsetY;
    Grid _grid;
};
