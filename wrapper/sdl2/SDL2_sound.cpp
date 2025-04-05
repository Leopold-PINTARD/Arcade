/*
** EPITECH PROJECT, 2025
** SDL2_sound.cpp
** File description:
** SDL2_sound.cpp
*/

#include <SDL2/SDL_mixer.h>
#include <string>
#include <utility>

#include "./SDL2.hpp"

void SDL2::playSound(const std::string &file, const std::string &id,
    bool loop, bool unique) {
    if (unique) {
        for (auto &sound : sounds) {
            if (sound.second.first == id)
                return;
        }
    }
    Mix_Chunk *sound = Mix_LoadWAV(file.c_str());
    int channel = -1;

    if (sound == nullptr) {
        getSDLError();
        exit(84);
    }
    if (loop)
        channel = Mix_PlayChannel(-1, sound, -1);
    else
        channel = Mix_PlayChannel(-1, sound, 0);
    if (channel == -1) {
        getSDLError();
        exit(84);
    }
    sounds.push_back(std::make_pair(sound, std::make_pair(id, channel)));
}

void SDL2::stopSound(const std::string &id, bool unique) {
    for (auto &sound : sounds) {
        if (sound.second.first == id && unique) {
            Mix_HaltChannel(sound.second.second);
            break;
        if (sound.second.first == id)
            Mix_HaltChannel(sound.second.second);
        }
    }
}
