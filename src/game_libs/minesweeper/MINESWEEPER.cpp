/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** MINESWEEPER
*/

#include "DataStructures/Sprite.hpp"
#include "DataStructures/Window.hpp"
#include "DataStructures/CLI_Colors.hpp"
#include "DataStructures/Event.hpp"
#include "modules/IGameModule.hpp"

#include "log/Log.hpp"
#include "game_libs/minesweeper/MINESWEEPER.hpp"

__attribute__((constructor)) void load(void) {
    Log::info() << "Loading MINESWEEPER game..." << std::endl;
}

__attribute__((destructor)) void unload(void) {
    Log::info() << "Unloading MINESWEEPER game..." << std::endl;
}

extern "C" std::unique_ptr<IGameModule> getGameModule() {
    Log::info() << "Entrypoint for MINESWEEPER game" << std::endl;
    return std::make_unique<MINESWEEPER>();
}

MINESWEEPER::MINESWEEPER() :
    _window(WINDOW_SIZE, "Arcade - Minesweeper", "assets/minesweeper/mine.png"),
    _gameRunning(true),
    _gameOver(false),
    _won(false),
    _offsetX((WINDOW_SIZE.first - _width * SIZE_SQUARE) / 2),
    _offsetY((WINDOW_SIZE.second - _height * SIZE_SQUARE) / 2),
    _width(GRID_SIZE_X),
    _height(GRID_SIZE_Y),
    _mines(GRID_MINES),
    _score(0),
    _grid(_width, _height, _mines) {
    initDrawableMap();
}

void MINESWEEPER::initDrawableMap(void) {
    initSquare("base", "assets/minesweeper/base.png", "[]",
        CLI_Color::CLI_WHITE, CLI_Color::CLI_BLACK);
    initSquare("mine", "assets/minesweeper/mine.png", "X ",
        CLI_Color::CLI_WHITE, CLI_Color::CLI_BLACK);
    initSquare("mine_exploded", "assets/minesweeper/mine_exploded.png", "X ",
        CLI_Color::CLI_RED, CLI_Color::CLI_BLACK);
    initSquare("flagged", "assets/minesweeper/flagged.png", "F ",
        CLI_Color::CLI_YELLOW, CLI_Color::CLI_BLACK);
    initSquare("revealed", "assets/minesweeper/revealed.png", "  ",
        CLI_Color::CLI_WHITE, CLI_Color::CLI_BLACK);
    initSquare("wtf", "assets/minesweeper/wtf.png", "W ",
        CLI_Color::CLI_WHITE, CLI_Color::CLI_BLACK);
    initSquare("wtf_pressed", "assets/minesweeper/wtf_pressed.png", "W ",
        CLI_Color::CLI_WHITE, CLI_Color::CLI_BLACK);
    initSquare("1", "assets/minesweeper/1.png", "1 ", CLI_Color::CLI_BLUE,
        CLI_Color::CLI_BLACK);
    initSquare("2", "assets/minesweeper/2.png", "2 ", CLI_Color::CLI_GREEN,
        CLI_Color::CLI_BLACK);
    initSquare("3", "assets/minesweeper/3.png", "3 ", CLI_Color::CLI_RED,
        CLI_Color::CLI_BLACK);
    initSquare("4", "assets/minesweeper/4.png", "4 ", CLI_Color::CLI_MAGENTA,
        CLI_Color::CLI_BLACK);
    initSquare("5", "assets/minesweeper/5.png", "5 ", CLI_Color::CLI_CYAN,
        CLI_Color::CLI_BLACK);
    initSquare("6", "assets/minesweeper/6.png", "6 ", CLI_Color::CLI_YELLOW,
        CLI_Color::CLI_BLACK);
    initSquare("7", "assets/minesweeper/7.png", "7 ", CLI_Color::CLI_WHITE,
        CLI_Color::CLI_BLACK);
    initSquare("8", "assets/minesweeper/8.png", "8 ", CLI_Color::CLI_WHITE,
        CLI_Color::CLI_BLACK);
}

void MINESWEEPER::initSquare(std::string name, std::string pathImage,
    std::string textCLI, CLI_Color frontColor, CLI_Color backColor) {
    Sprite sprite;
    sprite.setPosition(std::make_pair(0, 0));
    sprite.setScale(std::make_pair(2, 2));
    sprite.setRotation(0);
    sprite.setGUI_Color(std::make_tuple(255, 255, 255, 255));
    sprite.setCLI_Color(std::make_pair(backColor, frontColor));
    sprite.setAnimationTime(0);
    sprite.setCurrentTexture(0);
    sprite.setGUI_Textures({pathImage});
    sprite.setCLI_Textures({textCLI});
    _drawablesMap[name] = std::make_unique<Sprite>(sprite);
}

bool MINESWEEPER::update(float deltaTime) {
    (void)deltaTime;
    if (_gameOver) {
        return _gameRunning;
    }
    if (_grid.checkWin()) {
        _gameOver = true;
        _won = true;
        _score += 1000;
    }
    return _gameRunning;
}

const Window &MINESWEEPER::getWindow(void) { return _window; }

Text MINESWEEPER::createText(const std::string &str, int x, int y, CLI_Color
    frontColor, CLI_Color backColor, std::tuple<int, int, int, int> color,
    std::pair<float, float> scale) {
    Text text;
    text.setStr(str);
    text.setFontPath("assets/minesweeper/font.ttf");
    text.setPosition(std::make_pair(x, y));
    text.setScale(scale);
    text.setRotation(0);
    text.setCLI_Color(std::make_pair(backColor, frontColor));
    text.setGUI_Color(color);
    return text;
}

const std::vector<std::unique_ptr<IDrawable>> &MINESWEEPER::getDrawables(void) {
    _drawables.clear();

    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            Grid::Cell cell = _grid.getCell(x, y);
            std::unique_ptr<Sprite> cellSprite;

            if (cell.isFlagged) {
                cellSprite =
                    std::make_unique<Sprite>(*_drawablesMap["flagged"]);
            } else if (!cell.isRevealed) {
                cellSprite =
                    std::make_unique<Sprite>(*_drawablesMap["base"]);
            } else if (cell.type == Grid::MINE) {
                cellSprite =
                    std::make_unique<Sprite>(*_drawablesMap["mine_exploded"]);
            } else if (cell.adjacentMines == 0) {
                cellSprite =
                    std::make_unique<Sprite>(*_drawablesMap["revealed"]);
            } else {
                cellSprite = std::make_unique<Sprite>(*_drawablesMap
                    [std::to_string(cell.adjacentMines)]);
            }
            cellSprite->setPosition(std::make_pair(_offsetX + x *
                SIZE_SQUARE, _offsetY + y * SIZE_SQUARE));
            _drawables.push_back(std::move(cellSprite));
        }
    }
    if (_gameOver) {
        _drawables.push_back
            (std::make_unique<Text>(createText("Game Over", _offsetX + _width *
            SIZE_SQUARE / 2 - 50, _offsetY + _height * SIZE_SQUARE / 2,
            CLI_Color::CLI_RED, CLI_Color::CLI_BLACK,
            std::make_tuple(255, 0, 0, 255), SCALE)));
    }
    if (_won) {
        _drawables.push_back
            (std::make_unique<Text>(createText("You Won!", _offsetX + _width *
            SIZE_SQUARE / 2 - 50, _offsetY + _height * SIZE_SQUARE / 2,
            CLI_Color::CLI_GREEN, CLI_Color::CLI_BLACK,
            std::make_tuple(0, 255, 0, 255), SCALE)));
    }
    return _drawables;
}
const std::vector<Sound> &MINESWEEPER::getSound(void) { return _sounds; }

bool MINESWEEPER::event(const Event &events) {
    if (events.key == Key::KeyCode::ECHAP) {
        _gameRunning = false;
        return false;
    } else if (events.key == Key::KeyCode::KEY_R && _gameOver) {
        _grid = Grid(_width, _height, _mines);
        _gameOver = false;
        _won = false;
        _score = 0;
        return true;
    }
    if (_gameOver) {
        return true;
    }
    if (events.key == Key::KeyCode::MOUSE_LEFT ||
        events.key == Key::KeyCode::MOUSE_RIGHT) {
        return handleMouseEvent(events);
    }
    return true;
}

bool MINESWEEPER::handleMouseEvent(const Event &events) {
    try {
        auto mouseEvent = std::any_cast<std::pair<Key::MousePos,
            Key::KeyStatus>>(events.value);
        if (mouseEvent.second != Key::KeyStatus::KEY_PRESSED)
            return true;
        int gridX = (mouseEvent.first.x - _offsetX) / SIZE_SQUARE;
        int gridY = (mouseEvent.first.y - _offsetY) / SIZE_SQUARE;

        if (gridX >= 0 && gridX < _width && gridY >= 0 && gridY < _height) {
            Grid::Cell cell = _grid.getCell(gridX, gridY);
            if (events.key == Key::KeyCode::MOUSE_LEFT) {
                if (!cell.isFlagged && !cell.isRevealed) {
                    Grid::CellType cellType = _grid.revealCell(gridX, gridY);
                    if (cellType == Grid::MINE) {
                        _gameOver = true;
                        _won = false;
                        _grid.revealAllCells();
                    }
                    if (cellType != Grid::MINE) {
                        _score += 10;
                    }
                }
            } else if (events.key == Key::KeyCode::MOUSE_RIGHT) {
                if (!cell.isRevealed) {
                    if (cell.isFlagged) {
                        _grid.unflagCell(gridX, gridY);
                    } else {
                        _grid.flagCell(gridX, gridY);
                    }
                }
            }
        }
    } catch (const std::bad_any_cast &e) {
        Log::error() << "Error casting mouse event: " << e.what() << std::endl;
    }
    return true;
}

std::vector<std::pair<std::string, int>> MINESWEEPER::getScores(void) {
    std::vector<std::pair<std::string, int>> scores;
    scores.push_back(std::make_pair("Minesweeper", _score));
    return scores;
}
