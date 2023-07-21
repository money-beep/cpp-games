#ifndef SFML_TEMPLATE_SNAKEHEAD_HPP
#define SFML_TEMPLATE_SNAKEHEAD_HPP
#include "SFML/Graphics.hpp"
#include "constants.hpp"

constexpr int HEADSIZE = 20; // because every component is a square, there is no need for width and height

class SnakeHead {
private:
    sf::RectangleShape component;
    sf::Vector2i direction = {0, 0};
    sf::Vector2i lastMoveDirection = {0, 0};
public:
    SnakeHead(float mX, float mY) {
        component.setPosition(mX * GRIDSIZE, mY * GRIDSIZE);
        component.setSize(sf::Vector2f(HEADSIZE, HEADSIZE));
        component.setFillColor(sf::Color::Blue);
    }
    ~SnakeHead() = default;

    sf::RectangleShape getShape() const;
    float getX() const;
    float getY() const;
    sf::Vector2i getDirection() const;
    sf::Vector2i getLastMoveDirection() const;
    sf::Vector2i getGridPosition() const;
    sf::Vector2f getPosition() const;

    void setPosition(float mX, float mY);

    void updatePosition(sf::Vector2i position);
    void updateDirection();
};


#endif //SFML_TEMPLATE_SNAKEHEAD_HPP
