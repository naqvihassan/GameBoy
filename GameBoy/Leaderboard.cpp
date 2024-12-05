#include "Leaderboard.h"
#include <fstream>
#include "Game.h"
#include <iostream>


Leaderboard::Leaderboard(sf::RenderWindow* sharedWindow, InputSystem* input)
    : window(sharedWindow), inputSystem(input) {}


// Function to manually copy one char array to another
void copyCharArray(const char* source, char* destination, int size) {
    int i = 0;
    while (source[i] != '\0' && i < size - 1) { // Copy until the null character or limit reached
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0'; // Null-terminate the destination
}

bool compareCharArrays(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

void Leaderboard::updateScore(const char* playerName, int score, const char* gameName) {
    for (int i = 0; i < scoreCount; ++i) {
        if (compareCharArrays(highScores[i].playerName, playerName) &&
            compareCharArrays(highScores[i].gameName, gameName)) {
            if (score > highScores[i].score) {
                highScores[i].score = score; // Update score if the new score is higher
            }
            return;
        }
    }

    // If player not found, add new score
    if (scoreCount < 30) { // Limit to 30 scores (10 per game)
        copyCharArray(playerName, highScores[scoreCount].playerName, 50);
        copyCharArray(gameName, highScores[scoreCount].gameName, 20);
        highScores[scoreCount].score = score;
        scoreCount++;
    }

    // Sort scores in descending order (within the same game)
    for (int i = 0; i < scoreCount - 1; ++i) {
        for (int j = i + 1; j < scoreCount; ++j) {
            if (compareCharArrays(highScores[i].gameName, gameName) &&
                compareCharArrays(highScores[j].gameName, gameName) &&
                highScores[i].score < highScores[j].score) {
                // Swap scores and player names
                Score temp = highScores[i];
                highScores[i] = highScores[j];
                highScores[j] = temp;
            }
        }
    }
}

void Leaderboard::displayTopScores(const char* gameName) const {
    std::cout << "Top Scores for " << gameName << ":\n";
    for (int i = 0; i < scoreCount; ++i) {
        if (compareCharArrays(highScores[i].gameName, gameName)) {
            std::cout << highScores[i].playerName << ": " << highScores[i].score << '\n';
        }
    }
}
void Leaderboard::saveLeaderboard(const char* filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file for saving leaderboard.\n";
        return;
    }
    for (int i = 0; i < scoreCount; ++i) {
        file << highScores[i].playerName << " "
            << highScores[i].score << " "
            << highScores[i].gameName << "\n";
    }
}

void Leaderboard::loadLeaderboard(const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file to load leaderboard.\n";
        return;
    }

    scoreCount = 0;
    char name[50];
    int score;
    char game[20];
    while (file >> name >> score >> game) {
        copyCharArray(name, highScores[scoreCount].playerName, 50);
        copyCharArray(game, highScores[scoreCount].gameName, 20);
        highScores[scoreCount].score = score;
        scoreCount++;
    }
}

