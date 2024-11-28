// SnakeGame.cpp
#include "SnakeGame.h"

SnakeGame::SnakeGame(sf::RenderWindow* window) : window(window) {}

void SnakeGame::startGame() {
    std::cout << "SnakeGame started!" << std::endl;
}

void SnakeGame::update() {
    std::cout << "SnakeGame updating!" << std::endl;
}

void SnakeGame::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    // Render game objects here
    window.display();
}
