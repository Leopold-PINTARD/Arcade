/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Arcade
*/

#ifndef SRC_ARCADE_HPP_
#define SRC_ARCADE_HPP_

#include <chrono>
#include <memory>
#include <string>
#include <vector>

#include <modules/IDisplayModule.hpp>
#include <modules/IGameModule.hpp>

#include "./DLLoader.hpp"
#include "./log/Log.hpp"

class Arcade {
 public:
    explicit Arcade(std::string gfxLib) noexcept(false);
    Arcade(const Arcade &other) = delete;
    Arcade(Arcade &&other) = delete;
    Arcade &operator=(const Arcade &other) = delete;
    Arcade &operator=(Arcade &&other) = delete;
    Arcade() = delete;
    void run() noexcept(false);
    ~Arcade();

 protected:
 private:
    bool handleMenuEvent();
    bool handleGameEvent();
    void updateLibLists(std::string path);
    void menuLoop();
    void gameLoop();
    void cycleCurrentGfxLib();
    void cycleCurrentGameLib();
    bool eventStatusIs(Event::KeyStatus status, Event currentEvent);
    void switchGfxLib(std::string path, const Window &window);
    void switchGameLib(std::string path);
    std::chrono::_V2::system_clock::time_point _previousTime;
    std::chrono::_V2::system_clock::time_point _currentTime;
    bool _inMenu;
    DLLoader<IDisplayModule> _gfxLoader;
    DLLoader<IGameModule> _gameLoader;
    std::unique_ptr<IDisplayModule> &_displayModule;
    std::unique_ptr<IGameModule> &_gameModule;
    std::string _currentGfxLib;
    std::string _currentGameLib;
    std::vector<std::string> _gameModules;
    std::vector<std::string> _gfxModules;
};

#endif  // SRC_ARCADE_HPP_
