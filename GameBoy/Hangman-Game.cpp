#include "Hangman-Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

// Compare two character arrays
bool HangmanGame :: areStringsEqual(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return false;
        }
        ++str1;
        ++str2;
    }
    return *str1 == '\0' && *str2 == '\0';
}

//bool HangmanGame::shouldQuitToMenu() const {
//    return quitToMenu;
//}

// Copy one character array to another
void HangmanGame :: copyString(char* dest, const char* src) {
    while (*src) {
        *dest = *src;
        ++dest;
        ++src;
    }
    *dest = '\0'; // Null-terminate the destination string
}

// Clear a character array
void HangmanGame :: clearString(char* str, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        str[i] = '\0';
    }
}

// Main class implementation
HangmanGame::HangmanGame(sf::RenderWindow* sharedWindow, InputSystem* input)
    : window(sharedWindow), inputSystem(input), isGameOver(false), attemptsLeft(6), score(0), streak(0), hasWon(false), remainingTime(120), timeUp(false) {
    if (!font.loadFromFile("font/ARIAL.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    if (!backgroundTexture.loadFromFile("Hangman-Background.jpg")) {
        std::cerr << "Error loading background texture!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    float scaleX = static_cast<float>(1280) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(720) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    startGame();
}

void HangmanGame::startGame() {
    const char wordBank[][10] = { "program", "hangman", "game", "sfml", "coding" };
    int wordCount = 5;
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int randomIndex = std::rand() % wordCount;

    clearString(wordToGuess, 10);
    clearString(guessedWord, 10);

    // Copy word from wordBank to wordToGuess
    copyString(wordToGuess, wordBank[randomIndex]);

    // Initialize guessedWord with underscores
    for (int i = 0; wordToGuess[i] != '\0'; ++i) {
        guessedWord[i] = '_';
    }

    wordLength = 0;
    while (wordToGuess[wordLength] != '\0') {
        ++wordLength;
    }

    attemptsLeft = 6;
    for (int j = 0; j < 26; ++j) {
        guessedLetters[j] = false;
    }
    isGameOver = false;
    hasWon = false;
    timeUp = false;
}

void HangmanGame::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (hasWon) {
            streak++; // Increment streak if the previous word was correctly guessed
        }
        remainingTime = totalTime - gameClock.getElapsedTime().asSeconds();

        if (remainingTime <= 0) {
            remainingTime = 0;
            isGameOver = true;
            timeUp = true;
        }
        startGame(); // Restart the game
        return;
    }

    if (isGameOver) return;

    for (char c = 'A'; c <= 'Z'; ++c) {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(c - 'A' + sf::Keyboard::A))) {
            char guessedChar = static_cast<char>(tolower(c));
            int letterIndex = guessedChar - 'a';

            if (!guessedLetters[letterIndex]) {
                guessedLetters[letterIndex] = true;
                bool correct = false;

                for (int i = 0; i < wordLength; ++i) {
                    if (wordToGuess[i] == guessedChar) {
                        guessedWord[i] = guessedChar;
                        correct = true;
                        score += 10; // Increment score for each correct character
                    }
                }

                if (!correct) {
                    --attemptsLeft;
                }

                if (areStringsEqual(guessedWord, wordToGuess)) {
                    streak++; // Increment streak if the word is guessed correctly
                }

                isGameOver = attemptsLeft == 0 || areStringsEqual(guessedWord, wordToGuess);
                break;
            }
        }
    }
}

void HangmanGame::update() {
    handleInput();

    int elapsedTime = gameClock.getElapsedTime().asSeconds();
    if (elapsedTime >= totalTime) {
        isGameOver = true;
        timeUp = true; // Mark the game as ended due to time
    }
}

// Rest of the code (rendering logic, etc.) remains the same.

void HangmanGame::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite);

    // Calculate remaining time
    int elapsedTime = gameClock.getElapsedTime().asSeconds();
    int remainingTime = totalTime - elapsedTime;

    // Display remaining time
    char timerTextBuffer[50];
    sprintf_s(timerTextBuffer, "Time Left: %02d:%02d", remainingTime / 60, remainingTime % 60);
    sf::Text timerText(timerTextBuffer, font, 30);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(10, 55);
    window.draw(timerText);


    // Hangman structure on the left side
    sf::RectangleShape hangmanBase(sf::Vector2f(200, 10));
    hangmanBase.setPosition(100, 600);
    hangmanBase.setFillColor(sf::Color::White);
    window.draw(hangmanBase);

    sf::RectangleShape gallowsVertical(sf::Vector2f(10, 285));
    gallowsVertical.setPosition(150, 310);
    gallowsVertical.setFillColor(sf::Color::White);
    window.draw(gallowsVertical);

    sf::RectangleShape gallowsHorizontal(sf::Vector2f(100, 10));
    gallowsHorizontal.setPosition(150, 300);
    gallowsHorizontal.setFillColor(sf::Color::White);
    window.draw(gallowsHorizontal);

    sf::RectangleShape rope(sf::Vector2f(10, 50));
    rope.setPosition(240, 310);
    rope.setFillColor(sf::Color::White);
    window.draw(rope);

    // Draw hangman parts based on attempts left
    if (attemptsLeft <= 5) {
        sf::CircleShape head(30);
        head.setFillColor(sf::Color::Transparent);
        head.setOutlineThickness(5);
        head.setOutlineColor(sf::Color::Black);
        head.setPosition(210, 360);
        window.draw(head);
    }
    if (attemptsLeft <= 4) {
        sf::RectangleShape body(sf::Vector2f(10, 50));
        body.setPosition(240, 420);
        body.setFillColor(sf::Color::White);
        window.draw(body);
    }
    if (attemptsLeft <= 3) {
        // Left arm
        sf::RectangleShape leftArm(sf::Vector2f(45, 10));
        leftArm.setPosition(240, 440);
        leftArm.setFillColor(sf::Color::Black);
        leftArm.rotate(135); // Left arm angled upwards
        window.draw(leftArm);
    }
    if (attemptsLeft <= 2) {
        // Right arm
        sf::RectangleShape rightArm(sf::Vector2f(43, 10));
        rightArm.setPosition(260, 430);
        rightArm.setFillColor(sf::Color::Black);
        rightArm.rotate(45); // Right arm angled upwards
        window.draw(rightArm);
    }
    if (attemptsLeft <= 1) {
        // Left leg
        sf::RectangleShape leftLeg(sf::Vector2f(45, 10));
        leftLeg.setPosition(240, 470);
        leftLeg.setFillColor(sf::Color::Black);
        leftLeg.rotate(135); // Left leg angled downward
        window.draw(leftLeg);
    }
    if (attemptsLeft == 0) {
        // Right leg
        sf::RectangleShape rightLeg(sf::Vector2f(45, 10));
        rightLeg.setPosition(255, 465);
        rightLeg.setFillColor(sf::Color::Black);
        rightLeg.rotate(45); // Right leg angled downward
        window.draw(rightLeg);
    }

    // Display word and attempts on the right side
    float blankStartX = 800;
    float blankStartY = 300;
    float blankSpacing = 50;

    for (int i = 0; i < wordLength; ++i) {
        sf::RectangleShape blank(sf::Vector2f(40, 5));
        blank.setFillColor(sf::Color::White);
        blank.setPosition(blankStartX + i * blankSpacing, blankStartY);
        window.draw(blank);

        if (guessedWord[i] != '_') {
            sf::Text letter(std::string(1, guessedWord[i]), font, 40);
            letter.setFillColor(sf::Color::White);
            letter.setPosition(blankStartX + i * blankSpacing + 10, blankStartY - 50);
            window.draw(letter);
        }
    }

    sf::Text attemptsText("Attempts Left: " + std::to_string(attemptsLeft), font, 30);
    attemptsText.setFillColor(sf::Color::Red);
    attemptsText.setPosition(10, 7);
    window.draw(attemptsText);

    sf::Text scoreText("Score: " + std::to_string(score), font, 30);
    scoreText.setFillColor(sf::Color::Green);
    scoreText.setPosition(1100, 7);
    window.draw(scoreText);

    sf::Text streakText("Streak: " + std::to_string(streak), font, 30);
    streakText.setFillColor(sf::Color::Blue);
    streakText.setPosition(1100, 50);
    window.draw(streakText);

    // Draw the visual keyboard
   // Draw the visual keyboard
    float keyWidth = 40;
    float keyHeight = 40;
    float startX = 800;
    float startY = 500;
    int keyGap = 5;

    for (char c = 'A'; c <= 'Z'; ++c) {
        int index = c - 'A';
        int row = index / 10;
        int col = index % 10;

        sf::RectangleShape key(sf::Vector2f(keyWidth, keyHeight));
        key.setPosition(startX + col * (keyWidth + keyGap), startY + row * (keyHeight + keyGap));

       
        if (!guessedLetters[index]) {
            key.setFillColor(sf::Color::White); // Not guessed yet
        }
        else {
            // Check if the guessed letter is in the word
            bool isCorrect = false;
            for (int i = 0; i < wordLength; ++i) {
                if (wordToGuess[i] == tolower(c)) {
                    isCorrect = true;
                    break;
                }
            }
            key.setFillColor(isCorrect ? sf::Color::Green : sf::Color::Red); // Correct: Green, Incorrect: Red
        }

        window.draw(key);

        // Draw the letter on the key
        sf::Text keyText(std::string(1, c), font, 20);
        keyText.setFillColor(sf::Color::Black);
        keyText.setPosition(startX + col * (keyWidth + keyGap) + 10, startY + row * (keyHeight + keyGap) + 5);
        window.draw(keyText);
    }


    if (isGameOver) {

        if (timeUp)
        {
            sf::Text timeUpText("Time's Up! Game Over!", font, 50);
            timeUpText.setFillColor(sf::Color::Yellow);
            timeUpText.setPosition(400, 200);
            window.draw(timeUpText);
        }
        else
        {
            sf::Text gameOverText(strcmp(guessedWord, wordToGuess) == 0 ? "YOU WIN!" : "GAME OVER!", font, 50);
            gameOverText.setFillColor(strcmp(guessedWord, wordToGuess) == 0 ? sf::Color::Green : sf::Color::Red);
            gameOverText.setPosition(400, 100);
            window.draw(gameOverText);

            sf::Text restartText("Press SpaceBar to restart", font, 40);
            restartText.setFillColor(sf::Color::White);
            restartText.setPosition(450, 300);
            window.draw(restartText);
        }
    }

  //  window.display();
}

