#include "Ball.hpp"

sf::Vector2f Ball::getPosition() {
    return shape.getPosition();
}

float Ball::getRadius() {
    return shape.getRadius();
}

sf::CircleShape Ball::getShape() {
    return shape;
}


float Ball::getX() {
    return shape.getPosition().x;
}

float Ball::getY() {
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
    if (maxLeft() < 0) {
        velocity.x = BALLVELOCITY;
    } else if (maxRight() > 800) {
        velocity.x = -BALLVELOCITY;
    }
    if (maxTop() < 0) {
        velocity.y = BALLVELOCITY;
    } else if (maxBottom() > 600) {
        velocity.y = -BALLVELOCITY;
    }
}

void Ball::bounceBall() {
    velocity.y = -BALLVELOCITY;
}

void Ball::setXVelocity(bool position) {
    velocity.x = (position) ? -BALLVELOCITY : BALLVELOCITY;
}

void Ball::setYVelocity(bool position) {
    velocity.y = (position) ? -BALLVELOCITY : BALLVELOCITY;
}
