/*
** EPITECH PROJECT, 2025
** SDL2.hpp
** File description:
** SDL2.hpp
*/

#ifndef WRAPPER_SDL2_SDL2_HPP_
#define WRAPPER_SDL2_SDL2_HPP_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <vector>
#include <utility>

class SDL2 {
 public:
    SDL2();
    ~SDL2();

    void createWindow(const std::string &title, const std::string &iconPath,
                      int width, int height);
    void clearWindow(void);
    void displayWindow(void);

    struct KeyEvent {
        SDL_Keycode key;
        bool isPressed;
        int x;
        int y;
        float deltaTime;
    };
    void pollEvent(void);
    KeyEvent getKeyEvent(void);

    TTF_Font *loadFont(const std::string &file);
    SDL_Color getColor(std::tuple<int, int, int, int> color);
    void drawText(TTF_Font *font, const std::string text, SDL_Color color,
        std::pair<float, float> scale, float rotation, std::pair<int, int> pos);
    void drawSprite(const std::string &file, std::pair<float, float> scale,
        float rotation, std::pair<int, int> pos);

    void playSound(const std::string &file, const std::string &id, bool loop,
                   bool unique);
    void stopSound(const std::string &id, bool unique);

    void getSDLError(void);
    void getTTFError(void);

 private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    std::vector<KeyEvent> keyEvents;
    std::vector<std::pair<Mix_Chunk *, std::pair<std::string, int>>> sounds;
};

#endif  // WRAPPER_SDL2_SDL2_HPP_
