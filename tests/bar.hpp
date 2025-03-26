/*
** EPITECH PROJECT, 2025
** bsarcade
** File description:
** bar
*/

#ifndef TESTS_BAR_HPP_
    #define TESTS_BAR_HPP_

    #include <string>
    #include "ILib.hpp"

class Bar : public ILib {
 public:
    Bar();
    void init() override;
    void stop() override;
    const std::string &getName() const override;
    ~Bar() override;
 private:
    std::string _name;
};

#endif  // TESTS_BAR_HPP_
