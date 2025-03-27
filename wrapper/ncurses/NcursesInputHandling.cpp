/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NcursesInputHandling
*/

#include "wrapper/ncurses/Ncurses.hpp"
#include "src/log/Log.hpp"

Ncurses::Key Ncurses::getInput() {
    int ch = wgetch(_window);

    if (ch == ERR)
        return Key::NONE;
    auto it = _keyMap.find(ch);
    if (it != _keyMap.end())
        return it->second;
    return Key::NONE;
}

bool Ncurses::isKeyPressed() {
    int ch = wgetch(_window);

    if (ch != ERR) {
        ungetch(ch);
        return true;
    }
    return false;
}

void Ncurses::initKeyMap() {
    _keyMap[KEY_UP] = Key::UP;
    _keyMap[KEY_DOWN] = Key::DOWN;
    _keyMap[KEY_LEFT] = Key::LEFT;
    _keyMap[KEY_RIGHT] = Key::RIGHT;
    _keyMap['\n'] = Key::ENTER;
    _keyMap[27] = Key::ESCAPE;
    _keyMap[' '] = Key::SPACE;
    _keyMap[KEY_BACKSPACE] = Key::BACKSPACE;
    _keyMap['\t'] = Key::TAB;
    for (int i = 0; i < 26; i++) {
        _keyMap['a' + i] = static_cast<Key>(static_cast<int>(Key::A) + i);
        _keyMap['A' + i] = static_cast<Key>(static_cast<int>(Key::A) + i);
    }
    _keyMap['0'] = Key::NUM0;
    _keyMap['1'] = Key::NUM1;
    _keyMap['2'] = Key::NUM2;
    _keyMap['3'] = Key::NUM3;
    _keyMap['4'] = Key::NUM4;
    _keyMap['5'] = Key::NUM5;
    _keyMap['6'] = Key::NUM6;
    _keyMap['7'] = Key::NUM7;
    _keyMap['8'] = Key::NUM8;
    _keyMap['9'] = Key::NUM9;
    _keyMap[KEY_F(1)] = Key::F1;
    _keyMap[KEY_F(2)] = Key::F2;
    _keyMap[KEY_F(3)] = Key::F3;
    _keyMap[KEY_F(4)] = Key::F4;
    _keyMap[KEY_F(5)] = Key::F5;
    _keyMap[KEY_F(6)] = Key::F6;
    _keyMap[KEY_F(7)] = Key::F7;
    _keyMap[KEY_F(8)] = Key::F8;
    _keyMap[KEY_F(9)] = Key::F9;
    _keyMap[KEY_F(10)] = Key::F10;
    _keyMap[KEY_F(11)] = Key::F11;
    _keyMap[KEY_F(12)] = Key::F12;
}
