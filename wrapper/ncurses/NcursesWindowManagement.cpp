/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NcursesWindowManagement
*/

#include "wrapper/ncurses/Ncurses.hpp"

void Ncurses::resize(int width, int height) {
    if (_window == NULL) return;
    wresize(_window, height, width);
    wclear(_window);
    wrefresh(_window);
}

void Ncurses::clear() {
    if (_window == NULL) return;
    wclear(_window);
}

void Ncurses::erase() {
    if (_window == NULL) return;
    werase(_window);
}

void Ncurses::refresh() {
    if (_window == NULL) return;
    wrefresh(_window);
}

Ncurses::Coordinate Ncurses::getScreenSize() const {
    int x;
    int y;

    if (_window == NULL) return;
    getmaxyx(_window, y, x);
    return {x, y};
}

void Ncurses::defineColor(std::int16_t colorIndex, std::int16_t r,
                          std::int16_t g, std::int16_t b) {
    init_color(colorIndex, r, g, b);
}

std::unique_ptr<Ncurses> Ncurses::createSubWindow(int x, int y, int width,
                                                  int height) {
    WINDOW* subWindow = subwin(_window, height, width, y, x);
    std::unique_ptr<Ncurses> newWindow = std::make_unique<Ncurses>();

    newWindow->_window = subWindow;
    return newWindow;
}
