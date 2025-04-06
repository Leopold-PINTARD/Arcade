/*
** EPITECH PROJECT, 2025
** SDL2.cpp
** File description:
** SDL2.cpp
*/

#include <memory>
#include <iostream>
#include <map>
#include <utility>

#include "src/graphic_libs/SDL2.hpp"
#include "src/log/Log.hpp"
#include "DataStructures/Sprite.hpp"
#include "DataStructures/Text.hpp"

__attribute__((constructor)) void load(void) {
    Log::info() << "Loading SDL2 lib..." << std::endl;
}

__attribute__((destructor)) void unload(void) {
    Log::info() << "Unloading SDL2 lib..." << std::endl;
}

extern "C" std::unique_ptr<IDisplayModule> getDisplayModule(void) {
    Log::info() << "Entrypoint for SDL2 lib" << std::endl;
    return std::make_unique<libs::graphic::SDL2_DL>();
}

libs::graphic::SDL2_DL::SDL2_DL() {
    sdl2 = SDL2();
}

libs::graphic::SDL2_DL::~SDL2_DL() {
}

void libs::graphic::SDL2_DL::createWindow(const Window &window) {
    sdl2.createWindow(window.title, window.iconPath, window.size.first,
                      window.size.second);
}

std::map<SDL_Keycode, Key::KeyCode> libs::graphic::SDL2_DL::keys = {
    {SDLK_a, Key::KeyCode::KEY_A},
    {SDLK_b, Key::KeyCode::KEY_B},
    {SDLK_c, Key::KeyCode::KEY_C},
    {SDLK_d, Key::KeyCode::KEY_D},
    {SDLK_e, Key::KeyCode::KEY_E},
    {SDLK_f, Key::KeyCode::KEY_F},
    {SDLK_g, Key::KeyCode::KEY_G},
    {SDLK_h, Key::KeyCode::KEY_H},
    {SDLK_i, Key::KeyCode::KEY_I},
    {SDLK_j, Key::KeyCode::KEY_J},
    {SDLK_k, Key::KeyCode::KEY_K},
    {SDLK_l, Key::KeyCode::KEY_L},
    {SDLK_m, Key::KeyCode::KEY_M},
    {SDLK_n, Key::KeyCode::KEY_N},
    {SDLK_o, Key::KeyCode::KEY_O},
    {SDLK_p, Key::KeyCode::KEY_P},
    {SDLK_q, Key::KeyCode::KEY_Q},
    {SDLK_r, Key::KeyCode::KEY_R},
    {SDLK_s, Key::KeyCode::KEY_S},
    {SDLK_t, Key::KeyCode::KEY_T},
    {SDLK_u, Key::KeyCode::KEY_U},
    {SDLK_v, Key::KeyCode::KEY_V},
    {SDLK_w, Key::KeyCode::KEY_W},
    {SDLK_x, Key::KeyCode::KEY_X},
    {SDLK_y, Key::KeyCode::KEY_Y},
    {SDLK_z, Key::KeyCode::KEY_Z},
    {SDLK_0, Key::KeyCode::KEY_0},
    {SDLK_1, Key::KeyCode::KEY_1},
    {SDLK_2, Key::KeyCode::KEY_2},
    {SDLK_3, Key::KeyCode::KEY_3},
    {SDLK_4, Key::KeyCode::KEY_4},
    {SDLK_5, Key::KeyCode::KEY_5},
    {SDLK_6, Key::KeyCode::KEY_6},
    {SDLK_7, Key::KeyCode::KEY_7},
    {SDLK_8, Key::KeyCode::KEY_8},
    {SDLK_9, Key::KeyCode::KEY_9},
    {SDL_BUTTON_LEFT, Key::KeyCode::MOUSE_LEFT},
    {SDL_BUTTON_MIDDLE, Key::KeyCode::MOUSE_MIDDLE},
    {SDL_BUTTON_RIGHT, Key::KeyCode::MOUSE_RIGHT},
    {SDL_BUTTON_X1, Key::KeyCode::MOUSE_BUTTON_4},
    {SDL_BUTTON_X2, Key::KeyCode::MOUSE_BUTTON_5},
    {SDL_MOUSEWHEEL, Key::KeyCode::MOUSE_SCROLL},
    {SDL_MOUSEMOTION, Key::KeyCode::MOUSE_MOVE},
    {SDLK_SPACE, Key::KeyCode::SPACE},
    {SDLK_RETURN, Key::KeyCode::ENTER},
    {SDLK_TAB, Key::KeyCode::TAB},
    {SDLK_ESCAPE, Key::KeyCode::ECHAP},
    {SDLK_DELETE, Key::KeyCode::SUPPR},
    {SDLK_F1, Key::KeyCode::FUNCTION_1},
    {SDLK_F2, Key::KeyCode::FUNCTION_2},
    {SDLK_F3, Key::KeyCode::FUNCTION_3},
    {SDLK_F4, Key::KeyCode::FUNCTION_4},
    {SDLK_F5, Key::KeyCode::FUNCTION_5},
    {SDLK_F6, Key::KeyCode::FUNCTION_6},
    {SDLK_F7, Key::KeyCode::FUNCTION_7},
    {SDLK_F8, Key::KeyCode::FUNCTION_8},
    {SDLK_F9, Key::KeyCode::FUNCTION_9},
    {SDLK_F10, Key::KeyCode::FUNCTION_10},
    {SDLK_F11, Key::KeyCode::FUNCTION_11},
    {SDLK_F12, Key::KeyCode::FUNCTION_12},
    {SDLK_LEFT, Key::KeyCode::LEFT},
    {SDLK_RIGHT, Key::KeyCode::RIGHT},
    {SDLK_UP, Key::KeyCode::UP},
    {SDLK_DOWN, Key::KeyCode::DOWN},
    {SDLK_LSHIFT, Key::KeyCode::L_SHIFT},
    {SDLK_RSHIFT, Key::KeyCode::R_SHIFT},
    {SDLK_LCTRL, Key::KeyCode::L_CONTROL},
    {SDLK_RCTRL, Key::KeyCode::R_CONTROL},
    {SDLK_LALT, Key::KeyCode::ALT},
    {SDLK_RALT, Key::KeyCode::ALT}
};
