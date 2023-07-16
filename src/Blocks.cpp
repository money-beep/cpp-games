#include "Blocks.hpp"

sf::RectangleShape Blocks::getShape() const{
    return block;
}

void Blocks::setPosition(float mX, float mY) {
    block.setPosition(mX, mY);
}

float Blocks::getX() const{
    return block.getPosition().x;
}

float Blocks::getY() const{
    return block.getPosition().y;
}

float Blocks::maxLeft() {
    return getX() - (block.getSize().x / 2.f);
}

float Blocks::maxRight() {
    return getX() + (block.getSize().x / 2.f);
}

float Blocks::maxTop() {
    return getY() - block.getSize().y / 2.f;
}

float Blocks::maxBottom() {
    return getY() + block.getSize().y / 2.f;
}

void Blocks::setDestroyed() {
    destroyed = true;
}

bool Blocks::isDestroyed() const {
    return destroyed;
}