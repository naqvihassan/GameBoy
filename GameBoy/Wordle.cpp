#include "Wordle.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

// Compare two character arrays
bool Wordle::areStringsEqual(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return false;
        }
        ++str1;
        ++str2;
    }
    return *str1 == '\0' && *str2 == '\0';
}

// Copy one character array to another
void Wordle::copyString(char* dest, const char* src) {
    while (*src) {
        *dest = *src;
        ++dest;
        ++src;
    }
    *dest = '\0';
}

// Clear a character array
void Wordle::clearString(char* str, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        str[i] = '\0';
    }
}

// Constructor
Wordle::Wordle(sf::RenderWindow* sharedWindow, InputSystem* input)
    : window(sharedWindow), inputSystem(input), isGameOver(false), attemptsLeft(6), currentAttempt(0), currentColumn(0) , score(0), streak(0) {
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

// Initialize or reset the game
void Wordle::startGame() {
    const char wordBank[][6] = { "apple", "grape", "peach", "mango", "berry" };
    int wordCount = 5;

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int randomIndex = std::rand() % wordCount;

    clearString(wordToGuess, 6);
    copyString(wordToGuess, wordBank[randomIndex]);

    clearString(guessedWord, 6);
    currentAttempt = 0;
    currentColumn = 0;
    attemptsLeft = 6;

    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 5; ++j) {
            gridColors[i][j] = sf::Color(200, 200, 200); // Default grey for all cells
            guessedLetters[i][j] = '\0';                // Clear the guessed letters grid
        }
    }
    isGameOver = false;


}

    void Wordle::handleInput() {
        static bool keyPressed = false; // Track if a key was pressed in the previous frame

        if (isGameOver) return;

        // Handle letter input for the current row
        if (!keyPressed) { // Wait for key release before capturing the next key press
            for (char c = 'A'; c <= 'Z'; ++c) {
                if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(c - 'A' + sf::Keyboard::A))) {
                    if (currentColumn < 5 && currentAttempt < 6) { // Ensure within bounds of the row and attempt
                        guessedLetters[currentAttempt][currentColumn] = tolower(c); // Store the letter in the current column
                        ++currentColumn; // Move to the next column in the same row
                        keyPressed = true; // Mark key as pressed
                    }
                    break; // Exit the loop after registering a key press
                }
            }

            // Handle 'Backspace' press (remove the last entered letter)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                if (currentColumn > 0) { // Ensure there are letters to remove
                    --currentColumn; // Move back to the previous column
                    guessedLetters[currentAttempt][currentColumn] = '\0'; // Clear the letter in the current column
                    keyPressed = true; // Mark key as pressed
                }
            }

            // Handle 'Enter' press (submit the current guess)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                if (currentColumn == 5 && currentAttempt < 6) { // Ensure all 5 letters are filled in the row
                    processAttempt(); // Process the guess after the word is fully entered
                    keyPressed = true; // Mark key as pressed
                }
            }
        }

        // Reset keyPressed when no keys are being pressed
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            keyPressed = false; // Allow new key presses
        }
    }





void Wordle::processAttempt() {
    if (currentAttempt >= 6) return; // Prevent processing if we have no more attempts left

    // Check if the guessed word matches the target word
    if (areStringsEqual(guessedLetters[currentAttempt], wordToGuess)) {
        for (int i = 0; i < 5; ++i) {
            gridColors[currentAttempt][i] = sf::Color::Green;  // Correct letter, correct position
        }
        isGameOver = true;
        return;  // Correct guess, game over
    }

    // Temporary array to track matched letters in the word
    bool matched[5] = { false };

    // First pass: Mark correct positions (green)
    for (int i = 0; i < 5; ++i) {
        if (guessedLetters[currentAttempt][i] == wordToGuess[i]) {
            gridColors[currentAttempt][i] = sf::Color::Green;  // Correct letter, correct position
            matched[i] = true;
        }
    }

    // Second pass: Mark letters in the word but wrong position (yellow)
    for (int i = 0; i < 5; ++i) {
        if (gridColors[currentAttempt][i] == sf::Color::Green) continue;  // Skip already correct letters

        for (int j = 0; j < 5; ++j) {
            if (!matched[j] && guessedLetters[currentAttempt][i] == wordToGuess[j]) {
                gridColors[currentAttempt][i] = sf::Color::Yellow;  // Correct letter, wrong position
                matched[j] = true;
                break;
            }
        }

        // If still unmarked, mark as incorrect (grey)
        if (gridColors[currentAttempt][i] == sf::Color(200, 200, 200)) {
            gridColors[currentAttempt][i] = sf::Color(100, 100, 100);  // Incorrect letter
        }
    }

    // Move to the next attempt
    ++currentAttempt;
    currentColumn = 0;

    if (currentAttempt == 6) {
        isGameOver = true;  // Game over after 6 attempts
    }
}
void Wordle::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(backgroundSprite); // Draw the background

    // Wordle Grid Setup
    float gridStartX = 500;  // Starting X position for the grid
    float gridStartY = 130;  // Starting Y position for the grid
    float gridCellWidth = 60;  // Width of each grid cell
    float gridCellHeight = 60; // Height of each grid cell
    float gridSpacing = 10;    // Space between grid cells

    // Drawing the grid for 6 attempts and 5 columns
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 5; ++col) {
            sf::RectangleShape cell(sf::Vector2f(gridCellWidth, gridCellHeight));
            cell.setPosition(gridStartX + col * (gridCellWidth + gridSpacing),
                gridStartY + row * (gridCellHeight + gridSpacing));

            cell.setFillColor(gridColors[row][col]); // Set the color of the cell
            cell.setOutlineThickness(2);
            cell.setOutlineColor(sf::Color::Black); // Add a black border to the cell
            window.draw(cell);

            // Draw letters guessed in the grid
            if (guessedLetters[row][col] != '\0') {
                sf::Text letter(std::string(1, guessedLetters[row][col]), font, 30);
                letter.setFillColor(sf::Color::White); // Set the text color to white
                letter.setPosition(gridStartX + col * (gridCellWidth + gridSpacing) + 15,
                    gridStartY + row * (gridCellHeight + gridSpacing) + 10);
                window.draw(letter);
            }
        }
    }

    // Virtual Keyboard Setup
    float keyWidth = 40;
    float keyHeight = 40;
    float keyGap = 5;
    float keyboardStartX = 450; // Starting X position for the keyboard
    float keyboardStartY = 570; // Starting Y position for the keyboard

    std::string keyboardLayout = "QWERTYUIOPASDFGHJKLZXCVBNM";
    int keysPerRow[] = { 10, 9, 7 };
    int currentKey = 0;

    for (int row = 0; row < 3; ++row) {
        int keysInRow = keysPerRow[row];
        float rowStartX = keyboardStartX + (10 - keysInRow) * (keyWidth + keyGap) / 2;

        for (int col = 0; col < keysInRow; ++col) {
            sf::RectangleShape key(sf::Vector2f(keyWidth, keyHeight));
            key.setPosition(rowStartX + col * (keyWidth + keyGap),
                keyboardStartY + row * (keyHeight + keyGap));

            char letter = keyboardLayout[currentKey++];
            key.setFillColor(sf::Color(200, 200, 200)); // Default key color

            key.setOutlineThickness(2);
            key.setOutlineColor(sf::Color::Black);
            window.draw(key);

            // Draw the letter on the key
            sf::Text keyText(std::string(1, letter), font, 20);
            keyText.setFillColor(sf::Color::Black);
            keyText.setPosition(key.getPosition().x + 10, key.getPosition().y + 5);
            window.draw(keyText);
        }
    }

    // Display all drawn elements on the screen
    //window.display();
}

// Update the game state
void Wordle::update() {
    if (!isGameOver) {
        handleInput(); // Handle user input if the game is still active
    }

    // Restart the game if the spacebar is pressed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        startGame();
    }
}