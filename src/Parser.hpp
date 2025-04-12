/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Parser
*/

#ifndef SRC_PARSER_HPP_
#define SRC_PARSER_HPP_

#include <string>
#include <vector>

class Parser {
 public:
    Parser(int ac, char **av);
    Parser() = delete;
    ~Parser();
    class ParserException : public std::exception {
     public:
        explicit ParserException(const std::string &message)
            : _message(message) {}
        const char *what() const noexcept override { return _message.c_str(); }

     private:
        std::string _message;
    };
    std::vector<std::string> _args;

 protected:
 private:
};

#endif  // SRC_PARSER_HPP_
