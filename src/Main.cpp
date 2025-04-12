/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** main
*/

#include <iostream>

#include "./Arcade.hpp"

int main(int ac, char **av) {
    (void)ac;
    (void)av;
    try {
        Arcade arcade("./lib/arcade_sfmlother.so",
                      "./lib/arcade_minesweeper.so");
        arcade.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 84;
    }
    return 0;
}
