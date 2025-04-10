/*
** EPITECH PROJECT, 2025
** Arcade-Headers
** File description:
** Event
*/

#pragma once
#include <any>
#include <iostream>
#include <utility>

#include "Keys.hpp"

class Event {
 public:
    enum KeyStatus { KEY_PRESSED, KEY_RELEASED };

    struct MousePos {
        int x;
        int y;
    };

    struct MouseStatusClick {
        MousePos pos;
        KeyStatus status;
    };

    struct MouseStatusScroll {
        MousePos pos;
        float value;
    };

    Event(enum Key::KeyCode keyCode, std::any data)
        : key(keyCode), value(data) {
        // std::cout << "Event created with key: " << keyCode
        //           << ", data type: " << data.type().name() << std::endl;
    }
    ~Event() {
        // std::cout << "Event destroyed with key: " << key << std::endl;
    }
    // Event(const Event& other) : key(other.key), value(other.value) {
    //     std::cout << "Event copied with key: " << other.key << std::endl;
    // }
    // Event& operator=(const Event& other) {
    //     std::cout << "Copying event with key: " << other.key << std::endl;
    //     if (this != &other) {
    //         std::cout << "1" << std::endl;
    //         key = other.key;
    //         std::cout << "2" << std::endl;
    //         if (other.value.type() == typeid(MousePos)) {
    //             value = std::any_cast<MousePos>(other.value);
    //             std::cout << "2 pos" << std::endl;
    //         } else if (other.value.type() == typeid(MouseStatusClick)) {
    //             value = std::any_cast<MouseStatusClick>(other.value);
    //             std::cout << "2 lcick" << std::endl;
    //         } else if (other.value.type() == typeid(MouseStatusScroll)) {
    //             value = std::any_cast<MouseStatusScroll>(other.value);
    //             std::cout << "2 scroll" << std::endl;
    //         } else if (other.value.type() == typeid(int)) {
    //             value = std::any_cast<int>(other.value);
    //             std::cout << "2 int" << std::endl;
    //         } else if (other.value.type() == typeid(KeyStatus)) {
    //             value = std::any_cast<KeyStatus>(other.value);
    //             std::cout << "2 status" << std::endl;
    //         }
    //         std::cout << "3" << std::endl;
    //     }
    //     std::cout << "Event assigned with key: " << other.key << std::endl;
    //     return *this;
    // }

    const enum Key::KeyCode key;
    const std::any value;
};
