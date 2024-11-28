// Menu.h
#pragma once
#include <SFML/Graphics.hpp>
#include "InputSystem.h"

class Menu {
public:
    Menu();
    void draw(sf::RenderWindow& window);
    void handleClick(sf::RenderWindow& window, InputSystem& inputSystem);

private:
    void drawButton(sf::RenderWindow& window, const std::string& label, float x, float y);

    // Background image texture and sprite
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    // Button dimensions and position (added as member variables)
    float buttonWidth, buttonHeight;
    float buttonX, buttonY;
    float verticalSpacing;

    // Font for button text
    sf::Font font;
};
