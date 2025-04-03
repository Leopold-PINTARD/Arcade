/*
** EPITECH PROJECT, 2025
** SDL2.cpp
** File description:
** SDL2.cpp
*/

#include <SDL2/SDL_mixer.h>
#include <string>

#include "./SDL2.hpp"

void SDL2::playMusic(const std::string &file) {
    if (music != nullptr)
        Mix_FreeMusic(music);
    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        getSDLError();
        exit(84);
    }
    Mix_PlayMusic(music, -1);
}

void SDL2::stopMusic(void) {
    if (music != nullptr)
        Mix_HaltMusic();
}

void SDL2::pauseMusic(void) {
    if (music != nullptr)
        Mix_PauseMusic();
}

void SDL2::resumeMusic(void) {
    if (music != nullptr)
        Mix_ResumeMusic();
}

void SDL2::playSound(const std::string &file) {
    Mix_Chunk *sound = Mix_LoadWAV(file.c_str());

    if (sound == nullptr) {
        getSDLError();
        exit(84);
    }
    Mix_PlayChannel(-1, sound, 0);
}
