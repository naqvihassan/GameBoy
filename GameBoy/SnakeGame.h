#pragma once
#include <SFML/Graphics.hpp>
#include "Point.h"
#include "SnakeSegment.h"
#include "Grid.h"
#include "InputSystem.h"
#include "Game.h"

enum class Direction { Up, Down, Left, Right };

class SnakeGame : public Game {
public:
    SnakeGame(sf::RenderWindow* window, InputSystem* inputSystem);

    void startGame() override;
    void render(sf::RenderWindow& window) override;
    void update() override;

private:
    void handleInput();
    bool checkFoodCollision();
    void checkSelfCollision();
    void showGameOver();  // Function to show the game over message
    void restartGame();   // Function to restart the game when player presses 'R'

    sf::RenderWindow* window;
    InputSystem* inputSystem;
    static const int MAX_SNAKE_LENGTH = 500;
    SnakeSegment snake[MAX_SNAKE_LENGTH];
    int currentLength;
    Direction direction;
    Point food;
    Grid grid;
    bool isGameOver;
    bool isPaused;
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;

    sf::Texture backgroundTexture;  // Texture for the background image
    sf::Sprite backgroundSprite;    // Sprite for the background

    sf::Texture foodTexture;  // Texture for the food image
    sf::Sprite foodSprite;    // Sprite for displaying the food

    int score;
    const int cellSize = 40;

    sf::Clock clock1;
    float movementTimeAccumulator = 0.0f;
    const float timeStep = 0.1f;
};
