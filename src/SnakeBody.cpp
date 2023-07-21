#include "SnakeBody.hpp"

sf::RectangleShape SnakeBody::getShape() const {
    return component;
}

float SnakeBody::getX() const {
    return component.getPosition().x;
}

float SnakeBody::getY() const {
    return component.getPosition().y;
}

sf::Vector2i SnakeBody::getDirection() const {
    return direction;
};

sf::Vector2i SnakeBody::getGridPosition() const {
    sf::Vector2i temp;
    temp.x = component.getPosition().x / GRIDSIZE;
    temp.y = component.getPosition().y / GRIDSIZE;
    return temp;
}

sf::Vector2f SnakeBody::getPosition() const {
    return component.getPosition();
}

void SnakeBody::setDirection(sf::Vector2i direction) {
    this->direction = direction;
}

void SnakeBody::setPosition(float mX, float mY) {
    component.setPosition(mX * GRIDSIZE, mY * GRIDSIZE);
}

void SnakeBody::setPosition(sf::Vector2f position) {
    component.setPosition(position);
}

void SnakeBody::setPosition(sf::Vector2i position) {
    component.setPosition(position.x, position.y);
}

void SnakeBody::update(sf::Vector2i position) {
    component.setPosition(position.x * GRIDSIZE, position.y * GRIDSIZE);
}
