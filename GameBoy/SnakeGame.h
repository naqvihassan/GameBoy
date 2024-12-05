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
    bool shouldQuitToMenu() const override;

private:
    void handleInput();               // Handles keyboard input
    void checkSelfCollision();        // Checks if the snake collides with itself
    void checkBorderCollision();      // Checks if the snake hits the boundary
    bool checkFoodCollision();        // Checks if the snake eats food
    void showGameOver();              // Displays the game-over message
    void restartGame();               // Restarts the game
    void loadFont();                  // Loads fonts for text rendering
    void loadTextures();              // Loads textures for food and background
    void generateFood();              // Places food within valid bounds

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
    bool pausePressed;
    bool quitToMenu;  // Indicates if the user wants to quit to the menu
    int lastScoreForSpeedChange;  // Tracks the last score at which speed was adjusted
    //Direction lastDirection;  // Tracks the last direction used
    int level;

    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;

    sf::Texture foodTexture;          // Texture for the food image
    sf::Sprite foodSprite;            // Sprite for displaying the food
    sf::Texture backgroundTexture;    // Texture for the background image
    sf::Sprite backgroundSprite;      // Sprite for displaying the background

    int score;
    const int cellSize = 40;

    sf::Clock clock1;                 // Clock for tracking time
    float movementTimeAccumulator = 0.0f;
    float timeStep = 0.1f;

    // In your class
    sf::Clock gameClock;
    sf::Time elapsedTime;




};
