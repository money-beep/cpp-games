#include "Ball.hpp"

void Ball::setX(float mX) {
    shape.setPosition(mX, getY());
}

sf::CircleShape Ball::getShape() const{
    return shape;
}

float Ball::getX() const {
    return shape.getPosition().x;
}

float Ball::getY() const{
    return shape.getPosition().y;
}

float Ball::maxLeft() {
    return getX() - shape.getRadius();
}

float Ball::maxRight() {
    return getX() + shape.getRadius();
}

float Ball::maxTop() {
    return getY() - shape.getRadius();
}

float Ball::maxBottom() {
    return getY() + shape.getRadius();
}

void Ball::update() {
    shape.move(velocity);
    if(getY() <= 0){
        velocity.y = BALLVELOCITY;
    } else if(getY() >= 895){
        velocity.y = -BALLVELOCITY;
    }
}

void Ball::bounceHorizontally() {
    velocity.y = 0;
    velocity.x = (velocity.x > 0) ? -BALLVELOCITY : BALLVELOCITY;
}

void Ball::bounceDiagonally(bool direction) {
    if(direction){
        velocity.y = -BALLVELOCITY;
    } else {
        velocity.y = BALLVELOCITY;
    }
    velocity.x = (velocity.x > 0) ? -BALLVELOCITY : BALLVELOCITY;
}