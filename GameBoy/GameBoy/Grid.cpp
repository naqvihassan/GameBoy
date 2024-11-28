//// Grid.cpp
//#include "Grid.h"
//
//Grid::Grid(int width, int height) : width(width), height(height) {}
//
//// Grid.cpp
//void Grid::draw(sf::RenderWindow& window) {
//    sf::VertexArray lines(sf::Lines);
//
//    // Draw horizontal lines (change grid color to dark gray or black for better contrast)
//    for (int i = 0; i < height; i++) {
//        lines.append(sf::Vertex(sf::Vector2f(0, i * cellSize), sf::Color::White));  
//        lines.append(sf::Vertex(sf::Vector2f(width * cellSize, i * cellSize), sf::Color::White));
//    }
//
//    // Draw vertical lines
//    for (int i = 0; i < width; i++) {
//        lines.append(sf::Vertex(sf::Vector2f(i * cellSize, 0), sf::Color::White)); 
//        lines.append(sf::Vertex(sf::Vector2f(i * cellSize, height * cellSize), sf::Color::White));
//    }
//
//    window.draw(lines);
//}
//
