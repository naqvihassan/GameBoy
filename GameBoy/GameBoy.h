#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Game.h"
#include "InputSystem.h"
#include "Screen.h"  // Include the Screen class

class GameBoy {
public:
    GameBoy();                // Constructor
    void start();             // Main game loop
    void switchGame(Game* newGame);  // Switch to a different game

private:
    Screen screen;            // Use the Screen class for handling window and drawing
    InputSystem inputSystem;  // Handles input
    Menu* menu;               // Pointer to the menu
    Game* currentGame;        // Pointer to the active game
    bool isMenuActive;        // Flag to track if the menu is active
};
