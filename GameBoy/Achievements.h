#pragma once
#include <iostream>

struct Progress {
    int currentLevel;
    int totalPoints;
};

class AchievementSystem {
private:
    char achievements[10][50]; // Fixed-size array for up to 10 achievements, each of max 50 chars
    Progress progress;
    int achievementCount = 0; // To track how many achievements have been added

public:
    void trackAchievement(const char* achievement); // Add a new achievement
    void updateProgress(const Progress& progress); // Update current progress
    void displayAchievements() const; // Display all achievements
};
