// Menu.cpp
#include "Menu.h"
#include <iostream>

Menu::Menu() {
    // Load the background image
    if (!backgroundTexture.loadFromFile("background1.png")) {
        std::cout << "Error loading background image!" << std::endl;
    }

    // Scale the sprite to fit the window
    float scaleX = 1280.f / backgroundTexture.getSize().x;
    float scaleY = 720.f / backgroundTexture.getSize().y;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(scaleX, scaleY);

    // Button dimensions and position
    buttonWidth = 300.f;  // Width of the button
    buttonHeight = 75.f; // Height of the button
    buttonX = (1280 - buttonWidth) / 2; // Center horizontally
    buttonY = (720 - buttonHeight * 5) / 2; // Center vertically (5 buttons in total)

    // Vertical spacing between buttons
    verticalSpacing = buttonHeight + 20.f;

    // Load font for button text
    if (!font.loadFromFile("font/ARIAL.ttf")) {
        std::cout << "Error loading font!" << std::endl;
    }
}

void Menu::draw(sf::RenderWindow& window) {
    // Draw the background
    window.draw(backgroundSprite);

    // Draw the buttons
    drawButton(window, "Play Snake Game", buttonX, buttonY);
    drawButton(window, "Play Hangman Game", buttonX, buttonY + verticalSpacing);
    drawButton(window, "Play Wordle Game", buttonX, buttonY + verticalSpacing * 2);
    drawButton(window, "Records", buttonX, buttonY + verticalSpacing * 3);
    drawButton(window, "Exit", buttonX, buttonY + verticalSpacing * 4);
}

void Menu::handleClick(sf::RenderWindow& window, InputSystem& inputSystem) {
    sf::Vector2i mousePos = inputSystem.getMousePosition(window);

    // Check if mouse is within the bounds of the buttons
    if (mousePos.x >= buttonX && mousePos.x <= buttonX + buttonWidth) {
        // Check the Play Snake Game button
        if (mousePos.y >= buttonY && mousePos.y <= buttonY + buttonHeight) {
            if (inputSystem.isMousePressed()) {
                std::cout << "Play Snake Game button clicked!" << std::endl;
                // Start SnakeGame logic (to be implemented later)
            }
        }
        // Check the Play Hangman Game button
        else if (mousePos.y >= buttonY + verticalSpacing && mousePos.y <= buttonY + verticalSpacing + buttonHeight) {
            if (inputSystem.isMousePressed()) {
                std::cout << "Play Hangman Game button clicked!" << std::endl;
                // Start HangmanGame logic (to be implemented later)
            }
        }
        // Check the Play Wordle Game button
        else if (mousePos.y >= buttonY + verticalSpacing * 2 && mousePos.y <= buttonY + verticalSpacing * 2 + buttonHeight) {
            if (inputSystem.isMousePressed()) {
                std::cout << "Play Wordle Game button clicked!" << std::endl;
                // Start WordleGame logic (to be implemented later)
            }
        }
        // Check the Records button
        else if (mousePos.y >= buttonY + verticalSpacing * 3 && mousePos.y <= buttonY + verticalSpacing * 3 + buttonHeight) {
            if (inputSystem.isMousePressed()) {
                std::cout << "Records button clicked!" << std::endl;
                // Display records (to be implemented later)
            }
        }
        // Check the Exit button
        else if (mousePos.y >= buttonY + verticalSpacing * 4 && mousePos.y <= buttonY + verticalSpacing * 4 + buttonHeight) {
            if (inputSystem.isMousePressed()) {
                std::cout << "Exit button clicked!" << std::endl;
                window.close();  // Close the application
            }
        }
    }
}

void Menu::drawButton(sf::RenderWindow& window, const std::string& label, float x, float y) {
    // Create the button rectangle shape
    sf::RectangleShape button(sf::Vector2f(buttonWidth, buttonHeight));
    button.setFillColor(sf::Color::Green);
    button.setPosition(x, y);

    // Create the text for the button
    sf::Text text(label, font, 24); // Slightly larger font size for the button
    text.setFillColor(sf::Color::Black);

    // Center the text inside the button
    float textX = x + (buttonWidth - text.getGlobalBounds().width) / 2;
    float textY = y + (buttonHeight - text.getGlobalBounds().height) / 2 - 5;
    text.setPosition(textX, textY);

    // Draw the button and the text
    window.draw(button);
    window.draw(text);
}
