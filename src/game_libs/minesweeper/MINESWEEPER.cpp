/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** MINESWEEPER
*/

#include "log/Log.hpp"
#include "minesweeper/MINESWEEPER.hpp"

__attribute__((constructor)) void load(void) {
    Log::info() << "Loading MINESWEEPER game..." << std::endl;
}

__attribute__((destructor)) void unload(void) {
    Log::info() << "Unloading MINESWEEPER game..." << std::endl;
}

extern "C" std::unique_ptr<IGameModule> getGameModule() {
    Log::info() << "Entrypoint for MINESWEEPER game" << std::endl;
    return std::make_unique<MINESWEEPER>();
}

MINESWEEPER::MINESWEEPER() {
}

MINESWEEPER::~MINESWEEPER() {
}

bool update(float deltaTime);
const Window &getWindow(void);
const std::vector<std::unique_ptr<IDrawable>> &getDrawables(void);
const std::vector<Sound> &getSound(void);
bool event(const Event &events);
std::vector<std::pair<std::string, int>> getScores(void);
