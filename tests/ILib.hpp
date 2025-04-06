/*
** EPITECH PROJECT, 2025
** bsarcade
** File description:
** ILib
*/

#ifndef TESTS_ILIB_HPP_
#define TESTS_ILIB_HPP_

#include <string>

class ILib {
 public:
    virtual ~ILib() = default;
    virtual void init() = 0;
    virtual void stop() = 0;
    virtual const std::string &getName() const = 0;
};

#endif  // TESTS_ILIB_HPP_
