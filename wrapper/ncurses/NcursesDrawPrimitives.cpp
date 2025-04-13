/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NcursesDrawPrimitives
*/

#include <iostream>
#include <string>

#include "wrapper/ncurses/Ncurses.hpp"

void Ncurses::drawPixel(Ncurses::Coordinate xy, char c, Color fg, Color bg) {
    wattron(_window, COLOR_PAIR(getPairNumber(fg, bg)));
    mvwaddch(_window, xy.y, xy.x, c);
    wattroff(_window, COLOR_PAIR(getPairNumber(fg, bg)));
}

void Ncurses::drawText(Ncurses::Coordinate xy, const std::string& text,
                       Color fg, Color bg) {
    wattron(_window, COLOR_PAIR(getPairNumber(fg, bg)));
    mvwprintw(_window, xy.y, xy.x, "%s", text.c_str());
    wattroff(_window, COLOR_PAIR(getPairNumber(fg, bg)));
}

void Ncurses::drawRect(Ncurses::Coordinate xy, int width, int height, char c,
                       Color fg, Color bg) {
    wattron(_window, COLOR_PAIR(getPairNumber(fg, bg)));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            mvwaddch(_window, xy.y + y, xy.x + x, c);
        }
    }
    wattroff(_window, COLOR_PAIR(getPairNumber(fg, bg)));
}

void Ncurses::drawBox(Ncurses::Coordinate xy, int width, int height, Color fg,
                      Color bg) {
    wattron(_window, COLOR_PAIR(getPairNumber(fg, bg)));
    WINDOW* boxWin = subwin(_window, height, width, xy.y, xy.x);
    if (boxWin == NULL) {
        wattroff(_window, COLOR_PAIR(getPairNumber(fg, bg)));
    }
    if (box(boxWin, 0, 0) == ERR) {
        std::cerr << "Error creating subwindow" << std::endl;
    }
    if (wrefresh(boxWin) == ERR) {
        std::cerr << "Error refreshing subwindow" << std::endl;
    }
    if (delwin(boxWin) == ERR) {
        std::cerr << "Error deleting subwindow" << std::endl;
    }
    wattroff(_window, COLOR_PAIR(getPairNumber(fg, bg)));
}

void Ncurses::drawLine(Ncurses::Coordinate xy1, Ncurses::Coordinate xy2, char c,
                       Color fg, Color bg) {
    wattron(_window, COLOR_PAIR(getPairNumber(fg, bg)));
    if (wmove(_window, xy1.y, xy1.x) == ERR) {
        std::cerr << "Error moving to start position" << std::endl;
    }
    if (wvline(_window, c, xy2.x - xy1.x) == ERR) {
        std::cerr << "Error drawing line" << std::endl;
    }
    wattroff(_window, COLOR_PAIR(getPairNumber(fg, bg)));
}
