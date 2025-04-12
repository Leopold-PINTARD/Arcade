/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Arcade
*/

#ifndef SRC_ARCADE_HPP_
#define SRC_ARCADE_HPP_

#include <memory>
#include <string>

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
    bool handleEvent();
    DLLoader<IDisplayModule> _gfxLoader;
    DLLoader<IGameModule> _gameLoader;
    std::unique_ptr<IDisplayModule> &_displayModule;
    std::unique_ptr<IGameModule> &_gameModule;
};

#endif  // SRC_ARCADE_HPP_
