/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NcursesMouseHandling
*/

#include "wrapper/ncurses/Ncurses.hpp"

void Ncurses::enableMouse(bool enable) {
    if (enable) {
        mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
        printf("\033[?1003h\n");
        printf("\033[?1004h\n");
    } else {
        mousemask(0, NULL);
        printf("\033[?1003l\n");
        printf("\033[?1004l\n");
    }
}

void determineButton(Ncurses::MouseEvent& event, MEVENT& mevent) {
    if (mevent.bstate & BUTTON1_PRESSED)
        event.button = Ncurses::Button::LEFT;
    else if (mevent.bstate & BUTTON2_PRESSED)
        event.button = Ncurses::Button::MIDDLE;
    else if (mevent.bstate & BUTTON3_PRESSED)
        event.button = Ncurses::Button::RIGHT;
    else if (mevent.bstate & BUTTON4_PRESSED)
        event.button = Ncurses::Button::SCROLL_UP;
    else if (mevent.bstate & BUTTON5_PRESSED)
        event.button = Ncurses::Button::SCROLL_DOWN;
}

void determineEventTypes(Ncurses::MouseEvent& event, MEVENT& mevent) {
    if (mevent.bstate & BUTTON1_PRESSED)
        event.type = Ncurses::EventType::BUTTON_PRESS;
    else if (mevent.bstate & BUTTON1_RELEASED)
        event.type = Ncurses::EventType::BUTTON_RELEASE;
    else if (mevent.bstate & BUTTON1_CLICKED)
        event.type = Ncurses::EventType::BUTTON_CLICK;
    else if (mevent.bstate & BUTTON1_DOUBLE_CLICKED)
        event.type = Ncurses::EventType::BUTTON_DOUBLE_CLICK;
    else if (mevent.bstate & BUTTON1_TRIPLE_CLICKED)
        event.type = Ncurses::EventType::BUTTON_TRIPLE_CLICK;
    else if (mevent.bstate & REPORT_MOUSE_POSITION)
        event.type = Ncurses::EventType::BUTTON_MOTION;
}

void determineModifiers(Ncurses::MouseEvent& event, MEVENT& mevent) {
    if (mevent.bstate & BUTTON_SHIFT)
        event.shift = true;
    if (mevent.bstate & BUTTON_CTRL)
        event.ctrl = true;
    if (mevent.bstate & BUTTON_ALT)
        event.alt = true;
}

Ncurses::MouseEvent Ncurses::getMouseEvent() {
    MouseEvent event;
    event.type = EventType::NONE;
    event.button = Button::NONE;
    event.position = {0, 0};
    event.shift = false;
    event.ctrl = false;
    event.alt = false;
    MEVENT mevent;
    int result = getmouse(&mevent);

    if (result == ERR)
        return event;
    event.position.x = mevent.x;
    event.position.y = mevent.y;
    determineButton(event, mevent);
    determineEventTypes(event, mevent);
    determineModifiers(event, mevent);
    return event;
}
