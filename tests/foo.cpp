/*
** EPITECH PROJECT, 2025
** bsarcade
** File description:
** foo
*/

#include "foo.hpp"

#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

__attribute__((constructor)) void load(void) {
    std::cout << "[Start] Loading foo..." << std::endl;
}

__attribute__((destructor)) void unload(void) {
    std::cout << "[End] Unloading foo..." << std::endl;
}

extern "C" std::unique_ptr<ILib> create(void) {
    std::cout << "Entrypoint for foo!" << std::endl;
    return std::make_unique<Foo>();
}

Foo::Foo() : _name("Foo") {}

void Foo::init() { std::cout << "Foo init" << std::endl; }

void Foo::stop() { std::cout << "Foo stop" << std::endl; }

const std::string &Foo::getName() const { return _name; }

Foo::~Foo() {}
