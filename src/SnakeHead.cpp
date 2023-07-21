#include "SFML/Graphics.hpp"
#include "SnakeHead.hpp"

sf::RectangleShape SnakeHead::getShape() const{
    return component;
}

float SnakeHead::getX() const{
    return component.getPosition().x;
}

float SnakeHead::getY() const {
    return component.getPosition().y;
}

sf::Vector2i SnakeHead::getDirection() const {
    return direction;
}

sf::Vector2i SnakeHead::getLastMoveDirection() const {
    return lastMoveDirection;
}

sf::Vector2i SnakeHead::getGridPosition() const {
    sf::Vector2i temp;
    temp.x = component.getPosition().x / GRIDSIZE;
    temp.x = component.getPosition().x / GRIDSIZE;
    return temp;
}

sf::Vector2f SnakeHead::getPosition() const {
    return component.getPosition();
}

void SnakeHead::setPosition(float mX, float mY) {
    component.setPosition(mX, mY);
}

void SnakeHead::updatePosition(sf::Vector2i position) {
    if(position.x != component.getPosition().x / GRIDSIZE || position.y != component.getPosition().y / GRIDSIZE) {
        component.setPosition(position.x * GRIDSIZE, position.y * GRIDSIZE);
        lastMoveDirection = direction;
    }
}

void SnakeHead::updateDirection() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        direction.x = -1;
        direction.y = 0;
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        direction.x = 1;
        direction.y = 0;
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        direction.x = 0;
        direction.y = -1;
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        direction.x = 0;
        direction.y = 1;
    }
}