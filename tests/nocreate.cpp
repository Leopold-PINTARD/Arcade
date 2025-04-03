/*
** EPITECH PROJECT, 2025
** bsarcade
** File description:
** bar
*/

#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

#include "bar.hpp"

__attribute__((constructor)) void load(void) {
    std::cout << "[Start] Loading bar..." << std::endl;
}

__attribute__((destructor)) void unload(void) {
    std::cout << "[End] Unloading bar..." << std::endl;
}

extern "C" std::unique_ptr<ILib> nocreate(void) {
    std::cout << "Entrypoint for bar!" << std::endl;
    return std::make_unique<Bar>();
}

Bar::Bar() : _name("Bar") {}

void Bar::init() { std::cout << "Bar init" << std::endl; }

void Bar::stop() { std::cout << "Bar stop" << std::endl; }

const std::string &Bar::getName() const { return _name; }

Bar::~Bar() {}
