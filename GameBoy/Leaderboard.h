#pragma once
#include <iostream>
#include "InputSystem.h"
#include <SFML/Graphics.hpp>
#include "Game.h"

struct Score {
    char playerName[50]; // Fixed-size char array for player name
    int score;
    char gameName[20];   // Game name identifier (e.g., "Snake", "Hangman", "Wordle")
};

class Leaderboard {
private:
    Score highScores[30]; // Array to store scores (10 per game)
    int scoreCount = 0;   // Total scores stored
    sf::RenderWindow* window;
    InputSystem* inputSystem;
public:
    Leaderboard(sf::RenderWindow* sharedWindow, InputSystem* input);
    void updateScore(const char* playerName, int score, const char* gameName); // Update or add a new score
    void displayTopScores(const char* gameName) const; // Display top scores for a specific game
    void saveLeaderboard(const char* filename) const; // Save leaderboard to a file
    void loadLeaderboard(const char* filename); // Load leaderboard from a file
};
