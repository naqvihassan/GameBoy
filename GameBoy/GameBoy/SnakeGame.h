// SnakeGame.h
#pragma once
#include "Game.h"
#include <SFML/Graphics.hpp>  // Full inclusion for implementation

class SnakeGame : public Game {
public:
    SnakeGame(sf::RenderWindow* window);
    void startGame() override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    sf::RenderWindow* window;
};
