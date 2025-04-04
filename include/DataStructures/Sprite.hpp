/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Sprite
*/

#pragma once
#include <array>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <DataStructures/IDrawable.hpp>

class Sprite : public IDrawable {
 public:
    std::vector<std::string> getGUI_Textures(void) const {
        return GUI_Textures;
    }

    std::vector<std::string> getCLI_Textures(void) const {
        return CLI_Textures;
    }

    float getAnimationTime(void) const { return animationTime; }

    unsigned int getCurrentTexture(void) const { return currentTexture; }

    void setGUI_Textures(std::vector<std::string> GUI_Textures) {
        this->GUI_Textures = GUI_Textures;
    }

    void setCLI_Textures(std::vector<std::string> CLI_Textures) {
        this->CLI_Textures = CLI_Textures;
    }

    void setAnimationTime(float animationTime) {
        this->animationTime = animationTime;
    }

    void setCurrentTexture(unsigned int currentTexture) {
        this->currentTexture = currentTexture;
    }

    std::pair<float, float> getScale(void) const override { return scale; }

    float getRotation(void) const override { return rotation; }

    std::pair<CLI_Color, CLI_Color> getCLI_Color(void) const override {
        return CLI_color;
    }

    std::tuple<int, int, int, int> getGUI_Color(void) const override {
        return GUI_color;
    }

    std::pair<int, int> getPosition(void) const override { return position; }

    void setScale(std::pair<float, float> scale) override {
        this->scale = scale;
    }

    void setRotation(float rotation) override { this->rotation = rotation; }

    void setCLI_Color(std::pair<CLI_Color, CLI_Color> CLI_Color) override {
        this->CLI_color = CLI_Color;
    }

    void setGUI_Color(std::tuple<int, int, int, int> GUI_Color) override {
        this->GUI_color = GUI_Color;
    }

    void setPosition(std::pair<int, int> position) override {
        this->position = position;
    }

 private:
    std::vector<std::string> GUI_Textures;
    std::vector<std::string> CLI_Textures;
    float animationTime;
    unsigned int currentTexture;
    std::pair<float, float> scale;
    float rotation;
    std::pair<CLI_Color, CLI_Color> CLI_color;
    std::tuple<int, int, int, int> GUI_color;
    std::pair<int, int> position;
};
