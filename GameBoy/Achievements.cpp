#include "Achievements.h"
#include <iostream>

// Function to manually copy one char array to another
void copyCharArray1(const char* source, char* destination, int size) {
    int i = 0;
    while (source[i] != '\0' && i < size - 1) { // Copy until the null character or limit reached
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0'; // Null-terminate the destination array
}

void AchievementSystem::trackAchievement(const char* achievement) {
    if (achievementCount < 10) { // Limiting to 10 achievements
        copyCharArray1(achievement, achievements[achievementCount], 50);
        achievementCount++;
    }
}

void AchievementSystem::updateProgress(const Progress& newProgress) {
    progress = newProgress; // Simply update the progress struct
}

void AchievementSystem::displayAchievements() const {
    std::cout << "Achievements:\n";
    for (int i = 0; i < achievementCount; i++) {
        std::cout << "- " << achievements[i] << '\n';
    }
}
