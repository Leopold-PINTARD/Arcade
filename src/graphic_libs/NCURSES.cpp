/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NCURSES
*/

#include <string>
#include <cstdio>
#include <memory>
#include <iostream>
#include <tuple>
#include <map>
#include <vector>
#include <utility>

#include "src/graphic_libs/NCURSES.hpp"
#include "src/log/Log.hpp"
#include "include/DataStructures/Keys.hpp"
#include "include/DataStructures/CLI_Colors.hpp"
#include "include/DataStructures/Event.hpp"
#include "include/DataStructures/Window.hpp"
#include "include/DataStructures/Text.hpp"
#include "include/DataStructures/Sprite.hpp"

__attribute__((constructor)) void load(void) {
    Log::info() << "Loading NCURSES lib..." << std::endl;
}

__attribute__((destructor)) void unload(void) {
    Log::info() << "Unloading NCURSES lib..." << std::endl;
}

extern "C" std::unique_ptr<IDisplayModule> getDisplayModule(void) {
    Log::info() << "Entrypoint for NCURSES lib" << std::endl;
    return std::make_unique<libs::graphic::NCURSES>();
}

libs::graphic::NCURSES::NCURSES() : ncurses(Ncurses()) {
    ncurses = Ncurses();
}

libs::graphic::NCURSES::~NCURSES() {
}

void libs::graphic::NCURSES::createWindow(const Window &window) {
    ncurses.resize(window.size.first, window.size.second);
}

void libs::graphic::NCURSES::draw(const IDrawable &to_draw) {
    std::pair<int, int> position = to_draw.getPosition();
    std::pair<CLI_Color, CLI_Color> colors = to_draw.getCLI_Color();
    Ncurses::Color fg = Ncurses::Color::WHITE;
    Ncurses::Color bg = Ncurses::Color::BLACK;
    for (const auto &colorPair : this->colors) {
        if (colorPair.second == colors.first) {
            fg = colorPair.first;
        }
        if (colorPair.second == colors.second) {
            bg = colorPair.first;
        }
    }
    const Text *text = dynamic_cast<const Text *>(&to_draw);
    if (text != nullptr) {
        Ncurses::Coordinate coord = {position.first, position.second};
        ncurses.drawText(coord, text->getStr(), fg, bg);
        return;
    }
    const Sprite *sprite = dynamic_cast<const Sprite *>(&to_draw);
    if (sprite != nullptr) {
        unsigned int currentTexture = sprite->getCurrentTexture();
        std::vector<std::string> textures = sprite->getCLI_Textures();

        if (!textures.empty() && currentTexture < textures.size()) {
            Ncurses::Coordinate coord = {position.first, position.second};
            std::pair<float, float> scale = sprite->getScale();

            for (int y = 0; y < static_cast<int>(scale.second); y++) {
                for (int x = 0; x < static_cast<int>(scale.first); x++) {
                    Ncurses::Coordinate pixelCoord = {
                        coord.x + x,
                        coord.y + y
                    };
                    ncurses.drawPixel(pixelCoord, textures[currentTexture][0],
                        fg, bg);
                }
            }
        }
        return;
    }
    Ncurses::Coordinate coord = {position.first, position.second};
    ncurses.drawPixel(coord, 'X', fg, bg);
}

void libs::graphic::NCURSES::display(void) {
    ncurses.refresh();
}

void libs::graphic::NCURSES::clear(void) {
    ncurses.erase();
}

Event libs::graphic::NCURSES::getEvent(void) {
    if (ncurses.isKeyPressed()) {
        Ncurses::Key ncursesKey = ncurses.getInput();
        if (keys.find(ncursesKey) != keys.end()) {
            Key::KeyCode arcadeKey = keys[ncursesKey];
            return Event(arcadeKey, Key::KEY_PRESSED);
        }
    }
    Ncurses::MouseEvent mouseEvent = ncurses.getMouseEvent();
    if (mouseEvent.type != Ncurses::EventType::NONE) {
        if (mouseEvent.type == Ncurses::EventType::BUTTON_MOTION) {
            Key::MousePos pos = {mouseEvent.position.x, mouseEvent.position.y};
            return Event(Key::KeyCode::MOUSE_MOVE, pos);
        }
        if (mouse_buttons.find(mouseEvent.button) != mouse_buttons.end()) {
            Key::KeyCode buttonCode = mouse_buttons[mouseEvent.button];
            Key::MousePos pos = {mouseEvent.position.x, mouseEvent.position.y};
            return Event(buttonCode, pos);
        }
    }
    return Event(Key::KeyCode::NONE, Key::KEY_RELEASED);
}

void libs::graphic::NCURSES::handleSound(const Sound &sound) {
    // TODO(leopold) : handle sound if possible
    (void)sound;
}

std::map<Ncurses::Key, Key::KeyCode> libs::graphic::NCURSES::keys = {
    {Ncurses::Key::NONE, Key::KeyCode::NONE},

    {Ncurses::Key::A, Key::KeyCode::KEY_A},
    {Ncurses::Key::B, Key::KeyCode::KEY_B},
    {Ncurses::Key::C, Key::KeyCode::KEY_C},
    {Ncurses::Key::D, Key::KeyCode::KEY_D},
    {Ncurses::Key::E, Key::KeyCode::KEY_E},
    {Ncurses::Key::F, Key::KeyCode::KEY_F},
    {Ncurses::Key::G, Key::KeyCode::KEY_G},
    {Ncurses::Key::H, Key::KeyCode::KEY_H},
    {Ncurses::Key::I, Key::KeyCode::KEY_I},
    {Ncurses::Key::J, Key::KeyCode::KEY_J},
    {Ncurses::Key::K, Key::KeyCode::KEY_K},
    {Ncurses::Key::L, Key::KeyCode::KEY_L},
    {Ncurses::Key::M, Key::KeyCode::KEY_M},
    {Ncurses::Key::N, Key::KeyCode::KEY_N},
    {Ncurses::Key::O, Key::KeyCode::KEY_O},
    {Ncurses::Key::P, Key::KeyCode::KEY_P},
    {Ncurses::Key::Q, Key::KeyCode::KEY_Q},
    {Ncurses::Key::R, Key::KeyCode::KEY_R},
    {Ncurses::Key::S, Key::KeyCode::KEY_S},
    {Ncurses::Key::T, Key::KeyCode::KEY_T},
    {Ncurses::Key::U, Key::KeyCode::KEY_U},
    {Ncurses::Key::V, Key::KeyCode::KEY_V},
    {Ncurses::Key::W, Key::KeyCode::KEY_W},
    {Ncurses::Key::X, Key::KeyCode::KEY_X},
    {Ncurses::Key::Y, Key::KeyCode::KEY_Y},
    {Ncurses::Key::Z, Key::KeyCode::KEY_Z},

    {Ncurses::Key::UP, Key::KeyCode::UP},
    {Ncurses::Key::DOWN, Key::KeyCode::DOWN},
    {Ncurses::Key::LEFT, Key::KeyCode::LEFT},
    {Ncurses::Key::RIGHT, Key::KeyCode::RIGHT},

    {Ncurses::Key::ENTER, Key::KeyCode::ENTER},
    {Ncurses::Key::ESCAPE, Key::KeyCode::ECHAP},
    {Ncurses::Key::SPACE, Key::KeyCode::SPACE},
    {Ncurses::Key::BACKSPACE, Key::KeyCode::SUPPR},
    {Ncurses::Key::TAB, Key::KeyCode::TAB},

    {Ncurses::Key::NUM0, Key::KeyCode::KEY_0},
    {Ncurses::Key::NUM1, Key::KeyCode::KEY_1},
    {Ncurses::Key::NUM2, Key::KeyCode::KEY_2},
    {Ncurses::Key::NUM3, Key::KeyCode::KEY_3},
    {Ncurses::Key::NUM4, Key::KeyCode::KEY_4},
    {Ncurses::Key::NUM5, Key::KeyCode::KEY_5},
    {Ncurses::Key::NUM6, Key::KeyCode::KEY_6},
    {Ncurses::Key::NUM7, Key::KeyCode::KEY_7},
    {Ncurses::Key::NUM8, Key::KeyCode::KEY_8},
    {Ncurses::Key::NUM9, Key::KeyCode::KEY_9},

    {Ncurses::Key::F1, Key::KeyCode::FUNCTION_1},
    {Ncurses::Key::F2, Key::KeyCode::FUNCTION_2},
    {Ncurses::Key::F3, Key::KeyCode::FUNCTION_3},
    {Ncurses::Key::F4, Key::KeyCode::FUNCTION_4},
    {Ncurses::Key::F5, Key::KeyCode::FUNCTION_5},
    {Ncurses::Key::F6, Key::KeyCode::FUNCTION_6},
    {Ncurses::Key::F7, Key::KeyCode::FUNCTION_7},
    {Ncurses::Key::F8, Key::KeyCode::FUNCTION_8},
    {Ncurses::Key::F9, Key::KeyCode::FUNCTION_9},
    {Ncurses::Key::F10, Key::KeyCode::FUNCTION_10},
    {Ncurses::Key::F11, Key::KeyCode::FUNCTION_11},
    {Ncurses::Key::F12, Key::KeyCode::FUNCTION_12},
};

std::map<Ncurses::Button, Key::KeyCode> libs::graphic::NCURSES::mouse_buttons
    = {
    {Ncurses::Button::LEFT, Key::KeyCode::MOUSE_LEFT},
    {Ncurses::Button::MIDDLE, Key::KeyCode::MOUSE_MIDDLE},
    {Ncurses::Button::RIGHT, Key::KeyCode::MOUSE_RIGHT},
    {Ncurses::Button::SCROLL_UP, Key::KeyCode::MOUSE_BUTTON_4},
    {Ncurses::Button::SCROLL_DOWN, Key::KeyCode::MOUSE_BUTTON_5},
};

std::map<Ncurses::Color, CLI_Color> libs::graphic::NCURSES::colors = {
    {Ncurses::Color::BLACK, CLI_Color::CLI_BLACK},
    {Ncurses::Color::RED, CLI_Color::CLI_RED},
    {Ncurses::Color::GREEN, CLI_Color::CLI_GREEN},
    {Ncurses::Color::YELLOW, CLI_Color::CLI_YELLOW},
    {Ncurses::Color::BLUE, CLI_Color::CLI_BLUE},
    {Ncurses::Color::MAGENTA, CLI_Color::CLI_MAGENTA},
    {Ncurses::Color::CYAN, CLI_Color::CLI_CYAN},
    {Ncurses::Color::WHITE, CLI_Color::CLI_WHITE},
};
