#pragma once
#include <SFML/Graphics.hpp>
#include "InputSystem.h"
#include "Game.h"

class HangmanGame : public Game {
public:
    bool areStringsEqual(const char* str1, const char* str2);
    void copyString(char* dest, const char* src);
    void clearString(char* str, size_t length);
    HangmanGame(sf::RenderWindow* window, InputSystem* inputSystem);

    void startGame() ;       // Starting the game
    void render(sf::RenderWindow& window) override; // Renders the game
    void update() override;         // Updates game logic

private:
    void handleInput();             // Handles player input

    sf::RenderWindow* window;       // Pointer to the SFML window
    InputSystem* inputSystem;       // Input system for handling input

    sf::Font font;                  // Font for rendering text
    sf::Texture backgroundTexture;  // Background texture
    sf::Sprite backgroundSprite;    // Background sprite

    sf::Clock gameClock;  // Clock to track elapsed time
    int totalTime = 120;  // Total time in seconds (2 minutes)
    int remainingTime = 120;  // Total time in seconds (2 minutes)
    bool timeUp = false;  // Flag to check if time is up

    static const int maxWordLength = 10;
    char wordToGuess[maxWordLength]; // The word to guess
    char guessedWord[maxWordLength]; // Current state of guessed word
    int wordLength;                  // Length of the word to guess
    bool guessedLetters[26];        // Tracks guessed letters (a-z)
    bool hasWon;
    int attemptsLeft;                // Remaining attempts
    int streak;                // Streak for guessing the right word
    int score;                // Score after each word guessed right
    
    bool isGameOver;                 // Whether the game is over
};
