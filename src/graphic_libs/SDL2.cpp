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
