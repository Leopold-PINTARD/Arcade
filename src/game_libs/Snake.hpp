/*
** EPITECH PROJECT, 2025
** Snake.cpp
** File description:
** Snake.cpp
*/

#ifndef SRC_GAME_LIBS_SNAKE_HPP_
#define SRC_GAME_LIBS_SNAKE_HPP_

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <utility>

#include "modules/IGameModule.hpp"

namespace libs {
namespace game {

class Snake : public IGameModule {
 public:
     Snake();
     ~Snake();
     bool update(float deltaTime);
     const Window &getWindow(void);
     const std::vector<std::unique_ptr<IDrawable>> &getDrawables(void);
     const std::vector<Sound> &getSound(void);
     bool event(const Event &events);
     std::vector<std::pair<std::string, int>> getScores(void);

 private:
     bool isRunning;
     Window window;
     std::vector<std::unique_ptr<IDrawable>> drawables;
     std::unordered_map<std::string, std::unique_ptr<IDrawable>> drawablesMap;
     std::vector<Sound> sounds;
     std::vector<std::pair<std::string, int>> scores;

     void initDrawablesMap(void);
     void initDrawables(void);
     void initSounds(void);
     void initScores(void);

     int snakeLength;
     int appleCount;
     enum Direction {UP, DOWN, LEFT, RIGHT};
     Direction direction;
     std::vector<std::pair<int, int>> snakePosition;
     std::pair<int, int> applePosition;

     void moveSnake(void);
     bool checkCollision(void);
     void updateDrawables(void);
};

}  // namespace game
}  // namespace libs

#endif  // SRC_GAME_LIBS_SNAKE_HPP_
