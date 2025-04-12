/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Parser
*/

#include "Parser.hpp"

#include <iostream>
#include <string>

#include <modules/IDisplayModule.hpp>
#include <modules/IGameModule.hpp>

#include "DLLoader.hpp"

Parser::Parser(int ac, char **av) {
    if (ac < 2) throw ParserException("Not enough arguments");
    if (ac > 2) throw ParserException("Too many arguments");
    for (int i = 0; i < ac; ++i) _args.push_back(av[i]);
    try {
        DLLoader<IDisplayModule> gfxLoader(_args[1]);
        if (gfxLoader.entrypointExists("getDisplayModule") == false)
            throw ParserException(_args[1] + "Is not a graphic library");
    } catch (const DLLoader<IDisplayModule>::DLLoaderException &e) {
        throw ParserException("Failed to load graphic library " +
                              std::string(e.what()));
    }
}

Parser::~Parser() {}
