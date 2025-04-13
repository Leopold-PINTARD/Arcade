/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Ncurses
*/

#include "wrapper/ncurses/Ncurses.hpp"

#include <iostream>

Ncurses::Ncurses() { initialize(); }

Ncurses::Ncurses(int width, int height) {
    initialize();
    resize(width, height);
}

Ncurses::~Ncurses() { cleanup(); }

void Ncurses::initialize() {
    if (!_initialized) {
        _window = initscr();
        if (_window == NULL) {
            std::cerr << "Error initializing NCurses" << std::endl;
            exit(84);
        }
        _initialized = true;
        if (noecho() == ERR) {
            std::cerr << "Error setting noecho" << std::endl;
            exit(84);
        }
        if (curs_set(0) == ERR) {
            std::cerr << "Error setting cursor visibility" << std::endl;
            exit(84);
        }
        if (cbreak() == ERR) {
            std::cerr << "Error setting cbreak mode" << std::endl;
            exit(84);
        }
        if (keypad(_window, TRUE) == ERR) {
            std::cerr << "Error enabling keypad" << std::endl;
            exit(84);
        }
        if (start_color() == ERR) {
            std::cerr << "Error starting color mode" << std::endl;
            exit(84);
        }
        if (nodelay(_window, TRUE) == ERR) {
            std::cerr << "Error setting nodelay mode" << std::endl;
            exit(84);
        }
        initColors();
        initKeyMap();
    }
}

void Ncurses::cleanup() {
    if (_initialized) {
        if (_window != NULL && _window != stdscr) {
            if (delwin(_window)) {
                std::cerr << "Error deleting NCurses window" << std::endl;
                exit(84);
            }
            _window = NULL;
        }
        if (endwin() == ERR) {
            std::cerr << "Error ending NCurses mode" << std::endl;
            exit(84);
        }
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
