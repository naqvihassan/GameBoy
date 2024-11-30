#include "SnakeGame.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

SnakeGame::SnakeGame(sf::RenderWindow* sharedWindow, InputSystem* input)
    : window(sharedWindow), inputSystem(input), cellSize(40), isGameOver(false), isPaused(false),
    grid(1280 / 40, 720 / 40), direction(Direction::Right), currentLength(3), score(0) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Load font for score and game over text
    if (!font.loadFromFile("font/ARIAL.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over! Press R to Restart");
    gameOverText.setPosition(200, 300);

    // Load the food texture
    if (!foodTexture.loadFromFile("cheery2.png")) {
        std::cerr << "Error loading food texture!" << std::endl;
    }
    foodSprite.setTexture(foodTexture);
    foodSprite.setScale(static_cast<float>(cellSize) / foodTexture.getSize().x,
        static_cast<float>(cellSize) / foodTexture.getSize().y);

    // Load the background texture
    if (!backgroundTexture.loadFromFile("background_snake.png")) {  // Replace with your image path
        std::cerr << "Error loading background texture!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Scale the background to fit the window
    float scaleX = static_cast<float>(1280) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(720) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    startGame();
}

void SnakeGame::restartGame() {
    std::cout << "Restarting game..." << std::endl;
    startGame();
}


void SnakeGame::startGame() {
    isGameOver = false;
    isPaused = false;
    score = 0;
    currentLength = 3;  // Reset the snake length

    // Initialize snake
    for (int i = 0; i < currentLength; ++i) {
        snake[i] = SnakeSegment((grid.getWidth() / 2 - i) * cellSize, (grid.getHeight() / 2) * cellSize);
    }

    // Place food
    food.setPosition((std::rand() % grid.getWidth()) * cellSize, (std::rand() % grid.getHeight()) * cellSize);
    foodSprite.setPosition(static_cast<float>(food.x), static_cast<float>(food.y));

}

void SnakeGame::handleInput() {
    std::cout << "Handle Input";
    if (isPaused) return;

    //if (isGameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
    //    restartGame();  // Restart the game if 'R' is pressed
    //    return;
    //}

    // Process direction change based on keyboard input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && direction != Direction::Down) {
        direction = Direction::Up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && direction != Direction::Up) {
        direction = Direction::Down;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && direction != Direction::Right) {
        direction = Direction::Left;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && direction != Direction::Left) {
        direction = Direction::Right;
    }
}

void SnakeGame::update() {
    if (isGameOver) {
        // Allow input for restarting the game even if the game is over
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            restartGame();
        }
        return; // Skip the rest of the update logic
    }

    if (isPaused) return;

    // Get the time since the last frame (delta time)
    float deltaTime = clock1.restart().asSeconds();  // Restart clock and get the elapsed time
    movementTimeAccumulator += deltaTime;

    if (movementTimeAccumulator >= timeStep) {
        movementTimeAccumulator -= timeStep;

        // Move the snake body
        for (int i = currentLength - 1; i > 0; --i) {
            snake[i].setPosition(snake[i - 1].getPosition());
        }

        // Move the head based on direction
        Point newHead = snake[0].getPosition();
        if (direction == Direction::Up) newHead.y -= cellSize;
        else if (direction == Direction::Down) newHead.y += cellSize;
        else if (direction == Direction::Left) newHead.x -= cellSize;
        else if (direction == Direction::Right) newHead.x += cellSize;

        snake[0].setPosition(newHead);

        // Check food collision
        if (!checkFoodCollision()) {
            // Only check self-collision if no food was eaten
            checkSelfCollision();
        }
    }

    handleInput();
}


bool SnakeGame::checkFoodCollision() {
    if (snake[0].getPosition() == food) {
        if (currentLength < MAX_SNAKE_LENGTH) {
            snake[currentLength++] = SnakeSegment(snake[currentLength - 2].getPosition().x,
                snake[currentLength - 2].getPosition().y);
        }
        score += 10;

        // Place new food and update sprite position
        food.setPosition((std::rand() % grid.getWidth()) * cellSize, (std::rand() % grid.getHeight()) * cellSize);
        foodSprite.setPosition(static_cast<float>(food.x), static_cast<float>(food.y));

        return true;  // Food was eaten
    }
    return false;  // No food was eaten
}

void SnakeGame::checkSelfCollision() {
    for (int i = 1; i < currentLength; ++i) {
        if (snake[0].getPosition() == snake[i].getPosition()) {
            isGameOver = true;
        }
    }
}

void SnakeGame::showGameOver() {
    gameOverText.setString("Game Over! Press R to Restart");
    window->draw(gameOverText);
}

void SnakeGame::render(sf::RenderWindow& window) {
    window.clear();

    // Draw the background
    window.draw(backgroundSprite);

    // Draw the snake
    for (int i = 0; i < currentLength; ++i) {
        snake[i].draw(window);
    }

    // Draw the food
    window.draw(foodSprite);

    // Draw the score
    scoreText.setString("Score: " + std::to_string(score));
    window.draw(scoreText);

    if (isGameOver) {
        showGameOver();
    }
}
