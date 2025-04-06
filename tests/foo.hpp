/*
** EPITECH PROJECT, 2025
** bsarcade
** File description:
** foo
*/

#ifndef TESTS_FOO_HPP_
#define TESTS_FOO_HPP_

#include <string>

#include "ILib.hpp"

class Foo : public ILib {
 public:
    Foo();
    void init() override;
    void stop() override;
    const std::string &getName() const override;
    ~Foo() override;

 private:
    std::string _name;
};

#endif  // TESTS_FOO_HPP_
