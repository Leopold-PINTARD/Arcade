/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** testNcurseMemory
*/

#include "wrapper/ncurses/Ncurses.hpp"

int main()
{
    Ncurses ncurses;

    ncurses.resize(100, 100);
    ncurses.clear();
    ncurses.erase();
    ncurses.refresh();
    ncurses.getScreenSize();
    ncurses.defineColor(1, 100, 100, 100);
    ncurses.createSubWindow(0, 0, 100, 100);
    ncurses.enableMouse(true);
    ncurses.getMouseEvent();
    ncurses.isKeyPressed();
    ncurses.getInput();
    ncurses.setTimeout(100);
    ncurses.getPairNumber(Ncurses::Color::BLACK, Ncurses::Color::BLACK);
    return 0;
}