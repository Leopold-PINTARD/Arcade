/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NCURSES
*/

#pragma once

#include <map>
#include <memory>
#include <string>

#include "modules/IDisplayModule.hpp"
#include "wrapper/ncurses/Ncurses.hpp"

namespace libs {
namespace graphic {

class NCURSES : public IDisplayModule {
 public:
    static std::map<Ncurses::Key, Key::KeyCode> keys;
    static std::map<Ncurses::Button, Key::KeyCode> mouse_buttons;
    static std::map<Ncurses::Color, CLI_Color> colors;
    NCURSES();
    ~NCURSES();
    void createWindow(const Window &window) override;
    void draw(const IDrawable &to_draw) override;
    void display(void) override;
    void clear(void) override;
    Event getEvent(void) override;
    void handleSound(const Sound &sound) override;

 protected:
 private:
    Ncurses ncurses;
};

}  // namespace graphic
}  // namespace libs
