/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Sprite
*/

#pragma once
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <DataStructures/IDrawable.hpp>

class Sprite : public IDrawable {
 public:
    std::vector<std::string> getGUI_Textures(void) const;
    std::vector<std::string> getCLI_Textures(void) const;
    float getAnimationTime(void) const;
    unsigned int getCurrentTexture(void) const;
    void setGUI_Textures(std::vector<std::string> GUI_Textures);
    void setCLI_Textures(std::vector<std::string> CLI_Textures);
    void setAnimationTime(float animationTime);
    void setCurrentTexture(unsigned int currentTexture);

    std::pair<float, float> getScale(void) const override;
    float getRotation(void) const override;
    std::pair<CLI_Color, CLI_Color> getCLI_Color(void) const override;
    std::tuple<int, int, int, int> getGUI_Color(void) const override;
    std::pair<int, int> getPosition(void) const override;
    void setScale(std::pair<float, float> scale) override;
    void setRotation(float rotation) override;
    void setCLI_Color(std::pair<CLI_Color, CLI_Color> CLI_Color) override;
    void setGUI_Color(std::tuple<int, int, int, int> GUI_Color) override;
    void setPosition(std::pair<int, int> position) override;

 private:
    std::vector<std::string> GUI_Textures;
    std::vector<std::string> CLI_Textures;
    float animationTime;
    std::pair<float, float> scale;
    float rotation;
    std::pair<CLI_Color, CLI_Color> CLI_color;
    std::tuple<int, int, int, int> GUI_color;
    std::pair<int, int> position;
};
