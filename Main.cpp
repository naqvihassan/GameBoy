// Main.cpp
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "InputSystem.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "GameBoy");
    InputSystem inputSystem;
    Menu menu;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                inputSystem.setMousePressed(true);
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                inputSystem.setMousePressed(false);
            }
        }

        window.clear();
        menu.draw(window);
        menu.handleClick(window, inputSystem);

        window.display();
    }

    return 0;
}
