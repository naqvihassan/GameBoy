#pragma once
#include <SFML/Window.hpp>

class InputSystem {
public:
    InputSystem();
    void handleInput();  // Handle input and update direction
    bool isKeyPressed(sf::Keyboard::Key key);  // Check if a specific key is pressed
    sf::Keyboard::Key getDirection() const;  // Get the current direction of the snake

private:
    sf::Keyboard::Key direction;
};
