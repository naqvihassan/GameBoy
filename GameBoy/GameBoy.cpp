#include "GameBoy.h"
#include "SnakeGame.h"  // Include the SnakeGame header

GameBoy::GameBoy()
    : screen(1280, 720, "GameBoy"), currentGame(nullptr), isMenuActive(true) {
    menu = new Menu(&screen.getWindow(), &inputSystem, this);  // Passing the window from screen to menu
}

void GameBoy::start() {
    while (screen.isOpen()) {
        sf::Event event;
        while (screen.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                screen.close();
            }
        }

        screen.clear();  // Clear the screen before rendering

        if (isMenuActive) {
            std::cout << "Rendering Menu..." << std::endl;
            menu->draw();  // Draw the menu
            menu->handleClick();  // Handle button clicks
        }
        else if (currentGame) {
            std::cout << "Rendering SnakeGame..." << std::endl;
            currentGame->update();  // Update the game logic
            currentGame->render(screen.getWindow());  // Render the game
        }

        screen.display();  // Display the rendered content
    }
}




void GameBoy::switchGame(Game* newGame) {
    if (currentGame) {
        delete currentGame;  // Clean up the old game
        std::cout << "Previous game deleted." << std::endl;
    }
    else {
        std::cout << "No previous game to delete. Starting first game..." << std::endl;
    }

    currentGame = newGame;  // Set the new game
    currentGame->startGame();  // Start the new game
    isMenuActive = false;  // Deactivate the menu
    std::cout << "Switched to SnakeGame. Menu is now inactive." << std::endl;
}


