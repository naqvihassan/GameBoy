// InputSystem.cpp
#include "InputSystem.h"

InputSystem::InputSystem() : mousePressed(false) {}

void InputSystem::setMousePressed(bool pressed) {
    mousePressed = pressed;
}

bool InputSystem::isMousePressed() const {
    return mousePressed;
}

sf::Vector2i InputSystem::getMousePosition(sf::RenderWindow& window) const {
    return sf::Mouse::getPosition(window);
}
