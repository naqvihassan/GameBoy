#include "Menu.h"
#include "GameBoy.h"
#include <iostream>
#include "SnakeGame.h"
Menu::Menu(sf::RenderWindow* window, InputSystem* inputSystem, GameBoy* gameBoy)
    : window(window), inputSystem(inputSystem), gameBoy(gameBoy) {
    if (!backgroundTexture.loadFromFile("background1.png")) {
        std::cout << "Error loading background image!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    if (!font.loadFromFile("font/ARIAL.ttf")) {
        std::cout << "Error loading font!" << std::endl;
    }
}

void Menu::draw() {
    window->clear(sf::Color::Black); // Clear the screen before drawing
    window->draw(backgroundSprite); // Draw the background
    drawButton("Play Snake Game", 490, 200, 300, 75); // Draw the "Play Snake Game" button
    drawButton("Exit", 490, 300, 300, 75); // Draw the "Exit" button
}


void Menu::handleClick() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // Check button bounds for "Play Snake Game"
        if (mousePos.x >= 490 && mousePos.x <= 790 && mousePos.y >= 200 && mousePos.y <= 275) {
            std::cout << "Starting SnakeGame!" << std::endl;
            gameBoy->switchGame(new SnakeGame(window, inputSystem));  // Call switchGame
        }
        // Check button bounds for "Exit"
        else if (mousePos.x >= 490 && mousePos.x <= 790 && mousePos.y >= 300 && mousePos.y <= 375) {
            std::cout << "Exiting game!" << std::endl;
            window->close();  // Close the application
        }
    }
}




void Menu::drawButton(const std::string& label, float x, float y, float width, float height) {
    sf::RectangleShape button(sf::Vector2f(width, height));
    button.setPosition(x, y);
    button.setFillColor(sf::Color::Green);

    sf::Text text(label, font, 24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x + (width - text.getGlobalBounds().width) / 2, y + (height - text.getGlobalBounds().height) / 2);

    window->draw(button);
    window->draw(text);
}
