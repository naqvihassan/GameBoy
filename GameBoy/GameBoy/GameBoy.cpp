//// GameBoy.cpp
//#include "GameBoy.h"
//
//GameBoy::GameBoy() : screen(800, 600, "Game Boy"), currentGame(nullptr) {}
//
//void GameBoy::start() {
//    // Initial game state, for example, starting with the menu
//    menu.render(screen);
//    bool running = true;
//
//    while (running) {
//        inputSystem.handleInput();
//        screen.clear();
//
//        // Check for user input and handle game switching
//        if (inputSystem.isKeyPressed(sf::Keyboard::Enter)) {
//            // Switch to the SnakeGame for now
//            switchGame(new SnakeGame());
//        }
//
//        if (currentGame) {
//            currentGame->start();
//            screen.render(*currentGame);  // Render the active game
//        }
//
//        screen.display();
//    }
//}
//
//void GameBoy::switchGame(Game* game) {
//    if (currentGame) {
//        delete currentGame;  // Delete the current game
//    }
//    currentGame = game;  // Set the new game
//}
