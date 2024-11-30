#pragma once
#include <SFML/Graphics.hpp>
#include "InputSystem.h"

class GameBoy;  // Forward declaration to avoid circular dependency

class Menu {
public:
    Menu(sf::RenderWindow* window, InputSystem* inputSystem, GameBoy* gameBoy); // Constructor
    void draw();           // Draws the menu
    void handleClick();    // Handles button clicks

private:
    sf::RenderWindow* window;
    InputSystem* inputSystem;
    GameBoy* gameBoy; // Pointer to GameBoy for notifying about button clicks
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;

    void drawButton(const std::string& label, float x, float y, float width, float height); // Draws a button
};
