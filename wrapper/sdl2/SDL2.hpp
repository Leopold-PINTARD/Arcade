/*
** EPITECH PROJECT, 2025
** SDL2.hpp
** File description:
** SDL2.hpp
*/

#ifndef WRAPPER_SDL2_SDL2_HPP_
    #define WRAPPER_SDL2_SDL2_HPP_

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
    #include <SDL2/SDL_image.h>
    #include <vector>
    #include <string>

class SDL2 {
 public:
    SDL2();
    ~SDL2();

    void createWindow(const std::string &title,
        const std::string &iconPath, int width, int height);
    void clearWindow(void);
    void displayWindow(void);

    bool isRunning(void);

    struct MouseEvent {
        int x;
        int y;
        bool leftButton;
        bool rightButton;
        bool middleButton;
    };
    struct KeyEvent {
        SDL_Keycode key;
        bool isPressed;
    };
    void pollEvent(void);
    MouseEvent getMouseEvent(void);
    KeyEvent getKeyEvent(void);

    TTF_Font *loadFont(const std::string &file, int size);
    void drawText(TTF_Font *font, const std::string text,
        SDL_Color color, int x, int y);
    void drawSprite(const std::string &file, int x, int y);

    void getSDLError(void);
    void getTTFError(void);

 private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    bool running;
    MouseEvent mouseEvent;
    std::vector<KeyEvent> keyEvents;
};

#endif  // WRAPPER_SDL2_SDL2_HPP_
