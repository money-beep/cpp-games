#include "GridCell.hpp"

sf::Rect<float> GridCell::getGlobalBounds() const {
    return cell.getGlobalBounds();
}

sf::RectangleShape GridCell::getShape() const {
    return cell;
}

sf::Color GridCell::getFillColor() const {
    return cell.getFillColor();
}

bool GridCell::isBomb() const {
    return bomb;
}

bool GridCell::isRevealed() const {
    return revealed;
}

void GridCell::setFillColor(sf::Color color) {
    cell.setFillColor(color);
}

void GridCell::setBomb(bool bomb) {
    this->bomb = bomb;
}

void GridCell::setRevealed(bool revealed) {
    this->revealed = revealed;
}