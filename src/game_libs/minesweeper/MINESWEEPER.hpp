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
#include <unordered_map>
#include <tuple>

#include "modules/IGameModule.hpp"
#include "DataStructures/Text.hpp"
#include "Grid.hpp"

static const std::pair<int, int> WINDOW_SIZE =
    std::make_pair(1200, 800);

static const int GRID_SIZE_X = 10;
static const int GRID_SIZE_Y = 10;
static const int GRID_MINES = 10;

static const std::pair<float, float> SCALE =
    std::make_pair(1.0f, 1.0f);
static const int SIZE_SQUARE = 16;

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
    void initDrawableMap(void);
    void initSquare(std::string, std::string, std::string, CLI_Color,
      CLI_Color);
    bool handleMouseEvent(const Event &events);
    Text createText(const std::string &str, int x, int y, CLI_Color frontColor,
        CLI_Color backColor, std::tuple<int, int, int, int> color,
        std::pair<float, float> scale);
    std::vector<std::unique_ptr<IDrawable>> _drawables;
    std::unordered_map<std::string, std::unique_ptr<IDrawable>> _drawablesMap;
    std::vector<Sound> _sounds;
    Window _window;
    bool _gameRunning;
    bool _gameOver;
    bool _won;
    int _offsetX;
    int _offsetY;
    int _width;
    int _height;
    int _mines;
    unsigned int _score;
    Grid _grid;
};
