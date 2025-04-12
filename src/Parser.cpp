/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Parser
*/

#include "Parser.hpp"

#include <modules/IDisplayModule.hpp>
#include <modules/IGameModule.hpp>

#include "DLLoader.hpp"

Parser::Parser(int ac, char **av) {
    if (ac < 2) throw ParserException("Not enough arguments");
    for (int i = 1; i < ac; ++i) _args.push_back(av[i]);
    DLLoader<IDisplayModule> gfxLoader(_args[1]);
    if (gfxLoader.entrypointExists("getDisplayModule") == false)
        throw ParserException(_args[1] + "Is not a graphic library");
}

Parser::~Parser() {}
