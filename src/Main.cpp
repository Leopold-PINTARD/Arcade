/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** main
*/

#include <iostream>
#include <string>

#include "./Arcade.hpp"
#include "./Parser.hpp"

int main(int ac, char **av) {
    std::string gfxLib;

    try {
        Parser parse(ac, av);

        gfxLib = parse._args[1];
    } catch (const Parser::ParserException &e) {
        std::cerr << e.what() << '\n';
        return 84;
    }
    try {
        Arcade arcade(gfxLib);
        arcade.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 84;
    }
    return 0;
}
