#include "Platform.hpp"

sf::Vector2f Platform::getPosition() {
    return rectangle.getPosition();
}

sf::Vector2f Platform::getSize() {
    return rectangle.getSize();
}

sf::RectangleShape Platform::getShape() {
    return rectangle;
}

float Platform::getX() {
    return rectangle.getPosition().x;
}

float Platform::getY() {
    return rectangle.getPosition().y;
}

float Platform::maxLeft() {
    return getX() - (rectangle.getSize().x / 2.f);
}

float Platform::maxRight() {
    return getX() + (rectangle.getSize().x / 2.f);
}

float Platform::maxTop() {
    return getY() - rectangle.getSize().y / 2.f;
}

float Platform::maxBottom() {
    return getY() + rectangle.getSize().y / 2.f;
}

void Platform::update() {
    rectangle.move(velocity);
    if( sf::Keyboard::isKeyPressed(sf::Keyboard::A) && maxLeft() > 0){
        velocity.x = -PLATFORMVELOCITY;
    }else if( sf::Keyboard::isKeyPressed(sf::Keyboard::D) && maxRight() < 800){
        velocity.x = PLATFORMVELOCITY;
    } else velocity.x = 0;
}