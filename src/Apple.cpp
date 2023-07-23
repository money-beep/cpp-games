#include "Apple.hpp"

sf::CircleShape Apple::getShape() const {
    return component;
}

sf::Vector2i Apple::getGridPosition() const {
    sf::Vector2i temp;
    temp.x = component.getPosition().x / GRIDSIZE;
    temp.y = component.getPosition().y / GRIDSIZE;
    return temp;
}

void Apple::randomize() { // same as constructor
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> xDistribution(0, WIDTHGRID - 1);
    std::uniform_int_distribution<> yDistribution(0, HEIGHTGRID - 1);

    int x = xDistribution(gen) * GRIDSIZE;
    int y = yDistribution(gen) * GRIDSIZE;
    component.setPosition(x, y);
}