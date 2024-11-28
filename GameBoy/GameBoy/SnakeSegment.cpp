//// SnakeSegment.cpp
//#include "SnakeSegment.h"
//#include <SFML/Graphics.hpp>
//
////sf::Texture SnakeSegment::texture;  // Define the static texture variable here
//
//SnakeSegment::SnakeSegment(int x, int y, sf::Texture& texture) {
//    position.setPosition(x, y);
//    sprite.setPosition(x, y);
//    sprite.setTexture(texture);  // Use texture passed from SnakeGame
//    sprite.setScale(40.0f / texture.getSize().x, 40.0f / texture.getSize().y);
//}
//
//
//
//void SnakeSegment::setPosition(int x, int y) {
//    position.setPosition(x, y);
//    sprite.setPosition(x, y);
//}
//
//void SnakeSegment::setPosition(const Point& point) {
//    position = point;
//    sprite.setPosition(point.x, point.y);
//}
//
//Point SnakeSegment::getPosition() const {
//    return position;
//}
//
//void SnakeSegment::draw(sf::RenderWindow& window) const {
//    window.draw(sprite);  // Draw the segment on the screen
//}
