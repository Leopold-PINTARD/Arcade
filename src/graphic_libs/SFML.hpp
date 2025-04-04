/*
** EPITECH PROJECT, 2025
** bsarcade
** File description:
** bar
*/

#ifndef SRC_GRAPHIC_LIBS_SFML_HPP_
#define SRC_GRAPHIC_LIBS_SFML_HPP_

#include <map>
#include <memory>
#include <string>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "modules/IDisplayModule.hpp"

namespace libs {
namespace graphic {
class SFML : public IDisplayModule {
 public:
    static std::map<sf::Keyboard::Key, Key::KeyCode> keys;
    static std::map<sf::Mouse::Button, Key::KeyCode> mouse_buttons;
    SFML();
    void createWindow(const Window &window) override;
    void draw(const IDrawable &to_draw) override;
    void display(void) override;
    void clear(void) override;
    Event getEvent(void) override;
    void handleSound(const Sound &sound) override;
    ~SFML();

 private:
    std::unique_ptr<sf::RenderWindow> _window;
    std::map<std::string, sf::Sound> _sounds;
    std::map<std::string, sf::SoundBuffer> _soundBuffers;
};
}  // namespace graphic
}  // namespace libs

#endif  // SRC_GRAPHIC_LIBS_SFML_HPP_
