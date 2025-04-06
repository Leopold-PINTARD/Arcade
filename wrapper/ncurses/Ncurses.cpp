/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Ncurses
*/

#include "wrapper/ncurses/Ncurses.hpp"

Ncurses::Ncurses() { initialize(); }

Ncurses::Ncurses(int width, int height) {
    initialize();
    resize(width, height);
}

Ncurses::~Ncurses() { cleanup(); }

void Ncurses::initialize() {
    if (!_initialized) {
        _window = initscr();
        _initialized = true;
        noecho();
        cbreak();
        keypad(_window, TRUE);
        curs_set(0);
        start_color();
        nodelay(_window, TRUE);
        initColors();
        initKeyMap();
    }
}

void Ncurses::cleanup() {
    if (_initialized) {
        if (_window != nullptr && _window != stdscr) {
            delwin(_window);
            _window = nullptr;
        }
        endwin();
        _initialized = false;
    }
}

void Ncurses::initColors() {
    init_pair(0, COLOR_BLACK, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
}

std::int16_t Ncurses::getPairNumber(Color fg, Color bg) const {
    return static_cast<std::int16_t>(fg) + (static_cast<std::int16_t>(bg) * 8);
}

void Ncurses::setTimeout(int milliseconds) { timeout(milliseconds); }
