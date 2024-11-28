// InputSystem.h
#pragma once
#include <SFML/Graphics.hpp>

class InputSystem {
public:
    InputSystem();
    void setMousePressed(bool pressed);
    bool isMousePressed() const;
    sf::Vector2i getMousePosition(sf::RenderWindow& window) const;

private:
    bool mousePressed;
};
