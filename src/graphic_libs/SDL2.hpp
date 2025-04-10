/*
** EPITECH PROJECT, 2025
** SDL2.hpp
** File description:
** SDL2.hpp
*/

#ifndef SRC_GRAPHIC_LIBS_SDL2_HPP_
#define SRC_GRAPHIC_LIBS_SDL2_HPP_

#include <map>

#include "DataStructures/Event.hpp"
#include "DataStructures/Keys.hpp"
#include "modules/IDisplayModule.hpp"
#include "wrapper/sdl2/SDL2.hpp"

namespace libs {
namespace graphic {

class SDL2_DL : public IDisplayModule {
 public:
    static std::map<SDL_Keycode, Key::KeyCode> keys;
    SDL2_DL();
    ~SDL2_DL();
    void createWindow(const Window &window) override;
    void draw(const IDrawable &to_draw) override;
    void display(void) override;
    void clear(void) override;
    Event getEvent(void) override;
    void handleSound(const Sound &sound) override;

 private:
    SDL2 sdl2;
};

}  // namespace graphic
}  // namespace libs

#endif  // SRC_GRAPHIC_LIBS_SDL2_HPP_
