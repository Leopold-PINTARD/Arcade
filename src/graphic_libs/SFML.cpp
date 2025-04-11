/*
** EPITECH PROJECT, 2025
** bsarcade
** File description:
** SFML
*/

#include "./src/graphic_libs/SFML.hpp"

#include <cstdio>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <utility>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "./src/log/Log.hpp"
#include "DataStructures/Event.hpp"
#include "DataStructures/Keys.hpp"
#include "DataStructures/Sprite.hpp"
#include "DataStructures/Text.hpp"

__attribute__((constructor)) void load(void) {
    Log::info() << "Loading SFML lib..." << std::endl;
}

__attribute__((destructor)) void unload(void) {
    Log::info() << "Unloading SFML lib..." << std::endl;
}

extern "C" std::unique_ptr<IDisplayModule> getDisplayModule(void) {
    Log::info() << "Entrypoint for SFML lib" << std::endl;
    return std::make_unique<libs::graphic::SFML>();
}

libs::graphic::SFML::SFML() : _window(nullptr), _sounds(), _soundBuffers() {}

libs::graphic::SFML::~SFML() {
    if (this->_window != nullptr) {
        Log::info() << "Closing SFML window..." << std::endl;
        this->_window->close();
        this->_window.reset();
    }
}

void libs::graphic::SFML::createWindow(const Window &window) {
    if (this->_window != nullptr) {
        this->_window->setSize(
            sf::Vector2u(window.size.first * 20, window.size.second * 20));
        return;
    }
    if (this->_window == nullptr) {
        sf::Image icon;

        this->_window = std::make_unique<sf::RenderWindow>(
            sf::VideoMode(window.size.first * 20, window.size.second * 20),
            window.title);
        Log::info() << "Window created" << std::endl;
        if (icon.loadFromFile(window.iconPath) == false) {
            Log::error() << "Failed to load icon from path: " << window.iconPath
                         << std::endl;
            return;
        }
        Log::info() << "Icon loaded" << std::endl;
        this->_window->setIcon(icon.getSize().x, icon.getSize().y,
                               icon.getPixelsPtr());
    }
}

void libs::graphic::SFML::draw(const IDrawable &to_draw) {
    sf::Texture texture;

    if (this->_window == nullptr) {
        Log::info() << "draw(): No window open" << std::endl;
        return;
    }
    try {
        const Sprite &sprite = dynamic_cast<const Sprite &>(to_draw);
        sf::Texture texture;
        sf::Sprite sprite_sfml;
        std::tuple<int, int, int, int> color = sprite.getGUI_Color();

        if (!texture.loadFromFile(
                sprite.getGUI_Textures()[sprite.getCurrentTexture()]))
            Log::error() << "Failed to load texture from path: "
                         << sprite.getGUI_Textures()[sprite.getCurrentTexture()]
                         << std::endl;
        sprite_sfml.setTexture(texture);
        sprite_sfml.setColor(sf::Color(std::get<0>(color), std::get<1>(color),
                                       std::get<2>(color), std::get<3>(color)));
        sprite_sfml.setPosition(sprite.getPosition().first * 20,
                                sprite.getPosition().second * 20);
        sprite_sfml.setScale(sprite.getScale().first, sprite.getScale().second);
        sprite_sfml.setRotation(sprite.getRotation());
        this->_window->draw(sprite_sfml);
        return;
    } catch (const std::bad_cast &e) {
    }
    try {
        const Text &text = dynamic_cast<const Text &>(to_draw);
        sf::Text text_sfml;
        std::tuple<int, int, int, int> color = text.getGUI_Color();
        sf::Font font;

        if (!font.loadFromFile(text.getFontPath()))
            Log::error() << "Failed to load font from path: "
                         << text.getFontPath() << std::endl;
        text_sfml.setString(text.getStr());
        text_sfml.setScale(text.getScale().first, text.getScale().second);
        text_sfml.setPosition(text.getPosition().first * 20,
                              text.getPosition().second * 20);
        text_sfml.setFillColor(sf::Color(std::get<0>(color), std::get<1>(color),
                                         std::get<2>(color),
                                         std::get<3>(color)));
        text_sfml.setRotation(text.getRotation());
        text_sfml.setFont(font);
        this->_window->draw(text_sfml);
        return;
    } catch (const std::bad_cast &e) {
        Log::error() << "IDrawable is neither a sprite nor a text" << std::endl;
        Log::error() << e.what() << std::endl;
    }
}

void libs::graphic::SFML::display(void) {
    if (this->_window == nullptr) {
        Log::info() << "display(): No window open" << std::endl;
        return;
    }
    this->_window->display();
}

void libs::graphic::SFML::clear(void) {
    if (this->_window == nullptr) {
        Log::info() << "clear(): No window open" << std::endl;
        return;
    }
    this->_window->clear();
}

Event libs::graphic::SFML::getEvent(void) {
    sf::Event event;

    if (this->_window == nullptr) {
        Log::info() << "getEvent(): No window open" << std::endl;
        return Event(Key::NONE, std::any(0));
    }
    if (this->_window->pollEvent(event) == false) {
        return Event(Key::NONE, std::any(0));
    }
    if (event.type == sf::Event::Closed)
        return Event(Key::KeyCode::SUPPR,
                     std::any(Key::KeyStatus::KEY_PRESSED));
    if (event.type == sf::Event::KeyPressed)
        return Event(this->keys[event.key.code],
                     std::any(Key::KeyStatus::KEY_PRESSED));
    if (event.type == sf::Event::KeyReleased)
        return Event(this->keys[event.key.code],
                     std::any(Key::KeyStatus::KEY_RELEASED));
    if (event.type == sf::Event::MouseMoved)
        return Event(Key::KeyCode::MOUSE_MOVE,
                     std::any(Key::MousePos{event.mouseMove.x / 20,
                                            event.mouseMove.y / 20}));
    if (event.type == sf::Event::MouseButtonPressed)
        return Event(mouse_buttons[event.mouseButton.button],
                     std::any(Event::MouseStatusClick{
                         {event.mouseButton.x / 20, event.mouseButton.y / 20},
                         Event::KeyStatus::KEY_PRESSED}));
    if (event.type == sf::Event::MouseButtonReleased)
        return Event(mouse_buttons[event.mouseButton.button],
                     std::any(Event::MouseStatusClick{
                         {event.mouseButton.x / 20, event.mouseButton.y / 20},
                         Event::KeyStatus::KEY_RELEASED}));
    if (event.type == sf::Event::MouseWheelScrolled)
        return Event(Key::KeyCode::MOUSE_SCROLL,
                     std::any(Event::MouseStatusScroll{
                         Event::MousePos{event.mouseWheelScroll.x / 20,
                                         event.mouseWheelScroll.y / 20},
                         event.mouseWheelScroll.delta}));
    Log::info() << "getEvent(): Event unrecognized" << std::endl;
    return Event(Key::KeyCode::NONE, std::any(0));
}

void libs::graphic::SFML::handleSound(const Sound &sound) {
    if (this->_sounds.find(sound.id) == this->_sounds.end()) {
        sf::SoundBuffer buffer;
        sf::Sound sound_sfml;

        if (buffer.loadFromFile(sound.filePath) == false) return;
        sound_sfml.setBuffer(buffer);
        this->_soundBuffers[sound.id] = buffer;
        this->_sounds[sound.id] = sound_sfml;
    }
    if (sound.state == Sound::State::STOP) {
        this->_sounds[sound.id].setLoop(false);
        this->_sounds[sound.id].stop();
    }
    if (sound.state == Sound::State::PLAY) this->_sounds[sound.id].play();
    if (sound.state == Sound::State::LOOP) {
        this->_sounds[sound.id].setLoop(true);
        this->_sounds[sound.id].play();
    }
}

std::map<sf::Keyboard::Key, Key::KeyCode> libs::graphic::SFML::keys = {
    {sf::Keyboard::A, Key::KeyCode::KEY_A},
    {sf::Keyboard::B, Key::KeyCode::KEY_B},
    {sf::Keyboard::C, Key::KeyCode::KEY_C},
    {sf::Keyboard::D, Key::KeyCode::KEY_D},
    {sf::Keyboard::E, Key::KeyCode::KEY_E},
    {sf::Keyboard::F, Key::KeyCode::KEY_F},
    {sf::Keyboard::G, Key::KeyCode::KEY_G},
    {sf::Keyboard::H, Key::KeyCode::KEY_H},
    {sf::Keyboard::I, Key::KeyCode::KEY_I},
    {sf::Keyboard::J, Key::KeyCode::KEY_J},
    {sf::Keyboard::K, Key::KeyCode::KEY_K},
    {sf::Keyboard::L, Key::KeyCode::KEY_L},
    {sf::Keyboard::M, Key::KeyCode::KEY_M},
    {sf::Keyboard::N, Key::KeyCode::KEY_N},
    {sf::Keyboard::O, Key::KeyCode::KEY_O},
    {sf::Keyboard::P, Key::KeyCode::KEY_P},
    {sf::Keyboard::Q, Key::KeyCode::KEY_Q},
    {sf::Keyboard::R, Key::KeyCode::KEY_R},
    {sf::Keyboard::S, Key::KeyCode::KEY_S},
    {sf::Keyboard::T, Key::KeyCode::KEY_T},
    {sf::Keyboard::U, Key::KeyCode::KEY_U},
    {sf::Keyboard::V, Key::KeyCode::KEY_V},
    {sf::Keyboard::W, Key::KeyCode::KEY_W},
    {sf::Keyboard::X, Key::KeyCode::KEY_X},
    {sf::Keyboard::Y, Key::KeyCode::KEY_Y},
    {sf::Keyboard::Z, Key::KeyCode::KEY_Z},
    {sf::Keyboard::Space, Key::KeyCode::SPACE},
    {sf::Keyboard::Enter, Key::KeyCode::ENTER},
    {sf::Keyboard::Escape, Key::KeyCode::ECHAP},
    {sf::Keyboard::Left, Key::KeyCode::LEFT},
    {sf::Keyboard::Right, Key::KeyCode::RIGHT},
    {sf::Keyboard::Up, Key::KeyCode::UP},
    {sf::Keyboard::Down, Key::KeyCode::DOWN},
    {sf::Keyboard::Delete, Key::KeyCode::SUPPR},
    {sf::Keyboard::Tab, Key::KeyCode::TAB},
    {sf::Keyboard::Num0, Key::KeyCode::KEY_0},
    {sf::Keyboard::Num1, Key::KeyCode::KEY_1},
    {sf::Keyboard::Num2, Key::KeyCode::KEY_2},
    {sf::Keyboard::Num3, Key::KeyCode::KEY_3},
    {sf::Keyboard::Num4, Key::KeyCode::KEY_4},
    {sf::Keyboard::Num5, Key::KeyCode::KEY_5},
    {sf::Keyboard::Num6, Key::KeyCode::KEY_6},
    {sf::Keyboard::Num7, Key::KeyCode::KEY_7},
    {sf::Keyboard::Num8, Key::KeyCode::KEY_8},
    {sf::Keyboard::Num9, Key::KeyCode::KEY_9},
    {sf::Keyboard::F1, Key::KeyCode::FUNCTION_1},
    {sf::Keyboard::F2, Key::KeyCode::FUNCTION_2},
    {sf::Keyboard::F3, Key::KeyCode::FUNCTION_3},
    {sf::Keyboard::F4, Key::KeyCode::FUNCTION_4},
    {sf::Keyboard::F5, Key::KeyCode::FUNCTION_5},
    {sf::Keyboard::F6, Key::KeyCode::FUNCTION_6},
    {sf::Keyboard::F7, Key::KeyCode::FUNCTION_7},
    {sf::Keyboard::F8, Key::KeyCode::FUNCTION_8},
    {sf::Keyboard::F9, Key::KeyCode::FUNCTION_9},
    {sf::Keyboard::F10, Key::KeyCode::FUNCTION_10},
    {sf::Keyboard::F11, Key::KeyCode::FUNCTION_11},
    {sf::Keyboard::F12, Key::KeyCode::FUNCTION_12}};

std::map<sf::Mouse::Button, Key::KeyCode> libs::graphic::SFML::mouse_buttons = {
    {sf::Mouse::Left, Key::KeyCode::MOUSE_LEFT},
    {sf::Mouse::Middle, Key::KeyCode::MOUSE_MIDDLE},
    {sf::Mouse::Right, Key::KeyCode::MOUSE_RIGHT},
    {sf::Mouse::XButton1, Key::KeyCode::MOUSE_BUTTON_4},
    {sf::Mouse::XButton2, Key::KeyCode::MOUSE_BUTTON_5}};

//    {Key::KeyCode::MOUSE_LEFT, sf::Mouse::Left},
//    {Key::KeyCode::MOUSE_MIDDLE, sf::Mouse::Middle},
//    {Key::KeyCode::MOUSE_RIGHT, sf::Mouse::Right},
//    {Key::KeyCode::MOUSE_BUTTON_4, sf::Mouse::XButton1},
//    {Key::KeyCode::MOUSE_BUTTON_5, sf::Mouse::XButton2},
//    {Key::KeyCode::MOUSE_SCROLL, sf::Mouse::Wheel::VerticalWheel}
