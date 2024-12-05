#include "SnakeGame.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Constructor
SnakeGame::SnakeGame(sf::RenderWindow* sharedWindow, InputSystem* input)
    : window(sharedWindow), inputSystem(input), cellSize(40), isGameOver(false), isPaused(false),
    quitToMenu(false), grid(1280 / 40, 720 / 40), direction(Direction::Right), currentLength(3),
    score(0), movementTimeAccumulator(0.0f), timeStep(0.1f), pausePressed(false),
    lastScoreForSpeedChange(0) { // Initialize to 0
    loadFont();
    loadTextures();
    startGame();
}




// Load font for text rendering
void SnakeGame::loadFont() {
    if (!font.loadFromFile("font/ARIAL.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over! Press SPACE to Restart");
    gameOverText.setPosition(200, 300);
}

// Load textures for background and food
void SnakeGame::loadTextures() {
    if (!foodTexture.loadFromFile("cheery2.png")) {
        std::cerr << "Error loading food texture!" << std::endl;
    }
    foodSprite.setTexture(foodTexture);
    foodSprite.setScale(static_cast<float>(cellSize) / foodTexture.getSize().x,
        static_cast<float>(cellSize) / foodTexture.getSize().y);

    if (!backgroundTexture.loadFromFile("snake_background.png")) {
        std::cerr << "Error loading background texture!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(static_cast<float>(1280) / backgroundTexture.getSize().x,
        static_cast<float>(720) / backgroundTexture.getSize().y);
}

bool SnakeGame::shouldQuitToMenu() const {
    return quitToMenu;
}


// Start a new game
void SnakeGame::startGame() {

    gameClock.restart();
    isGameOver = false;
    isPaused = false;
    score = 0;
    currentLength = 3;
    direction = Direction::Right;
    movementTimeAccumulator = 0.0f;
    timeStep = 0.1f;
    lastScoreForSpeedChange = 0;  // Reset when game starts
    for (int i = 0; i < currentLength; ++i) {
        snake[i] = SnakeSegment((grid.getWidth() / 2 - i) * cellSize, (grid.getHeight() / 2) * cellSize);
    }
    generateFood();
    clock1.restart();
}


// Restart the game
void SnakeGame::restartGame() {
    std::cout << "Restarting game..." << std::endl;
    for (int i = currentLength; i < MAX_SNAKE_LENGTH; ++i) {
        snake[i].setPosition(-cellSize, -cellSize);  // Move unused segments off-screen
    }
    startGame();
}

void SnakeGame::handleInput() {
    // Toggle pause/resume with "P"
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && !pausePressed) {
        isPaused = !isPaused;  // Toggle the pause state
        pausePressed = true;
        if (isPaused) {
            std::cout << "Game Paused" << std::endl;
        }
        else {
            std::cout << "Game Resumed" << std::endl;
            clock1.restart();  // Reset clock to avoid time jump after resuming
        }
    }

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
        pausePressed = false; // Reset pausePressed when key is released
    }

    if (isPaused || isGameOver) return;  // Skip input handling if paused or game over

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

    // Handle quitting to menu (if applicable)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
        quitToMenu = true;  // Signal to return to the menu
    }
}

void SnakeGame::update() {
    if (isGameOver) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            restartGame();
        }
        return;
    }

    handleInput();

    if (isPaused) return;

    // Get elapsed time since the game started
    elapsedTime = gameClock.getElapsedTime();


    // Increase speed every 100 points only once
    if (score >= lastScoreForSpeedChange + 200) {  // Adjust speed if score increased by 100 since last adjustment
        timeStep = std::max(0.05f, timeStep - 0.005f);  // Gradual speed increase
        lastScoreForSpeedChange = score;  // Update the last score for speed change
        std::cout << "Speed increased! New timeStep: " << timeStep << std::endl;
    }

    float deltaTime = clock1.restart().asSeconds();
    movementTimeAccumulator += deltaTime;

    if (movementTimeAccumulator >= timeStep) {
        movementTimeAccumulator -= timeStep;

        // Move the snake body
        for (int i = currentLength - 1; i > 0; --i) {
            snake[i].setPosition(snake[i - 1].getPosition());
        }

        // Move the head
        Point newHead = snake[0].getPosition();
        if (direction == Direction::Up) newHead.y -= cellSize;
        else if (direction == Direction::Down) newHead.y += cellSize;
        else if (direction == Direction::Left) newHead.x -= cellSize;
        else if (direction == Direction::Right) newHead.x += cellSize;

        snake[0].setPosition(newHead);

        checkBorderCollision();
        if (!checkFoodCollision()) {
            checkSelfCollision();
        }
    }
}








// Generate new food within bounds
void SnakeGame::generateFood() {
    food.setPosition((std::rand() % grid.getWidth()) * cellSize,
        (std::rand() % ((720 - 120) / cellSize)) * cellSize + 120);
    foodSprite.setPosition(static_cast<float>(food.x), static_cast<float>(food.y));
}

// Check food collision
bool SnakeGame::checkFoodCollision() {
    if (snake[0].getPosition() == food) {
        if (currentLength < MAX_SNAKE_LENGTH) {
            // Correcting Food Collision Growth
            if (currentLength < MAX_SNAKE_LENGTH) {
                Point lastSegmentPosition = snake[currentLength - 1].getPosition();
                snake[currentLength++] = SnakeSegment(lastSegmentPosition.x, lastSegmentPosition.y);
            }

        }
        score += 10;
        generateFood();
        return true;
    }
    return false;
}

// Check self-collision
void SnakeGame::checkSelfCollision() {
    // Skip self-collision check for the first 2 segments behind the head
    int startIndex = (currentLength > 3) ? 2 : currentLength; 

    for (int i = startIndex; i < currentLength; ++i) {
        if (snake[0].getPosition() == snake[i].getPosition()) {
            std::cout << "Self-collision detected!" << std::endl;
            isGameOver = true;
            return;
        }
    }
}


// Check boundary collision
void SnakeGame::checkBorderCollision() {
    Point head = snake[0].getPosition();
    if (head.x < 0 || head.x >= 1280 || head.y < 120 || head.y >= 720) {
        std::cout << "Boundary collision detected!" << std::endl;
        isGameOver = true;
    }
}

// Render game elements
void SnakeGame::render(sf::RenderWindow& window) {
    window.clear();

    window.draw(backgroundSprite);

    for (int i = 0; i < currentLength; ++i) {
        snake[i].draw(window);
    }

    window.draw(foodSprite);

    scoreText.setString("Score: " + std::to_string(score));
    window.draw(scoreText);

    if (isGameOver) {
        window.draw(gameOverText);
    }

    if (isPaused) {
        sf::Text pausedText;
        pausedText.setFont(font);
        pausedText.setString("Game Paused\nPress P to Resume");
        pausedText.setCharacterSize(40);
        pausedText.setFillColor(sf::Color::Yellow);
        pausedText.setPosition(400, 300);
        window.draw(pausedText);
    }

    // Draw elapsed time at the top-right of the screen
    sf::Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(1100, 10);
    timeText.setString("Time: " + std::to_string(static_cast<int>(elapsedTime.asSeconds())) + "s");
    window.draw(timeText);


}
