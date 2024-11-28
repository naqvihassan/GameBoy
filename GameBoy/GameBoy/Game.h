// Game.h
#pragma once
#include <iostream>
using namespace std;

// Forward declaration of sf::RenderWindow
namespace sf {
    class RenderWindow;
}

class Game {
public:
    virtual void startGame() = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual ~Game() {}
};
