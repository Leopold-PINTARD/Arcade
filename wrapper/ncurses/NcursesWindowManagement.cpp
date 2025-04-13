/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NcursesWindowManagement
*/

#include <iostream>

#include "wrapper/ncurses/Ncurses.hpp"

void Ncurses::resize(int width, int height) {
    if (_window == NULL) return;
    if (wresize(_window, height, width) == ERR) {
        std::cerr << "Error resizing window" << std::endl;
        return;
    }
    clear();
    refresh();
}

void Ncurses::clear() {
    if (_window == NULL) return;
    if (wclear(_window) == ERR) {
        std::cerr << "Error clearing window" << std::endl;
        return;
    }
}

void Ncurses::erase() {
    if (_window == NULL) return;
    if (werase(_window) == ERR) {
        std::cerr << "Error erasing window" << std::endl;
        return;
    }
}

void Ncurses::refresh() {
    if (_window == NULL) return;
    if (wrefresh(_window) == ERR) {
        std::cerr << "Error refreshing window" << std::endl;
        return;
    }
}

Ncurses::Coordinate Ncurses::getScreenSize() const {
    int x;
    int y;

    if (_window == NULL) return {0, 0};
    getmaxyx(_window, y, x);
    return {x, y};
}

void Ncurses::defineColor(std::int16_t colorIndex, std::int16_t r,
                          std::int16_t g, std::int16_t b) {
    if (init_color(colorIndex, r, g, b) == ERR) {
        std::cerr << "Error defining color" << std::endl;
        return;
    }
}

std::unique_ptr<Ncurses> Ncurses::createSubWindow(int x, int y, int width,
                                                  int height) {
    WINDOW *subWindow = subwin(_window, height, width, y, x);
    std::unique_ptr<Ncurses> newWindow = std::make_unique<Ncurses>();

    if (subWindow == NULL) {
        std::cerr << "Error creating sub-window" << std::endl;
        return nullptr;
    }
    newWindow->_window = subWindow;
    return newWindow;
}
