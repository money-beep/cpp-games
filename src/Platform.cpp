#include "Platform.hpp"

sf::RectangleShape Platform::getShape() const{
    return shape;
}

float Platform::getHeight() const {
    return shape.getSize().y;
}

float Platform::getX() const {
    return shape.getPosition().x;
}

float Platform::getY() const{
    return shape.getPosition().y;
}

float Platform::maxLeft() {
    return getX() - (shape.getSize().x / 2.f);
}

float Platform::maxRight() {
    return getX() + (shape.getSize().x / 2.f);
}

float Platform::maxTop() {
    return getY() - shape.getSize().y / 2.f;
}

float Platform::maxBottom() {
    return getY() + shape.getSize().y / 2.f;
}

void Platform::update() {
    shape.move(velocity);
    if( sf::Keyboard::isKeyPressed(bindUp) && getY() > 0){
        velocity.y = -PLATFORMVELOCITY;
    }else if( sf::Keyboard::isKeyPressed(bindDown) && getY() < 900){
        velocity.y = PLATFORMVELOCITY;
    } else velocity.y = 0;
}