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

        if (isMenuActive) {
            menu->draw();
            menu->handleClick();

            // Add a delay to debounce input when returning to the menu
            sf::sleep(sf::milliseconds(100));
        }
        else if (currentGame) {
            currentGame->update();

            if (currentGame->shouldQuitToMenu()) {
                isMenuActive = true;
                delete currentGame;
                currentGame = nullptr;

                // Reset the screen and input system
                inputSystem.isKeyPressed(sf::Keyboard::Unknown);  // Clear any previous key press (use an unused key)
                screen.clear();
                screen.display();
                sf::sleep(sf::milliseconds(100));  // Debounce input
                continue;
            }

            currentGame->render(screen.getWindow());
        }

        screen.display();
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


