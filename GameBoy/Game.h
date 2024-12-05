#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Game {
public:
    virtual void startGame() = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual bool shouldQuitToMenu() const { return false; }
    virtual ~Game() {}
};
