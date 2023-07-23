#ifndef SFML_TEMPLATE_SNAKEBODY_HPP
#define SFML_TEMPLATE_SNAKEBODY_HPP
#include "SFML/Graphics.hpp"
#include "constants.hpp"

constexpr int COMPONENTSIZE = 20;

class SnakeBody {
private:
    sf::RectangleShape component;
    sf::Vector2i direction;
public:
    SnakeBody(float mX, float mY, sf::Vector2i direction) {
        component.setPosition(mX * GRIDSIZE, mY * GRIDSIZE);
        component.setSize(sf::Vector2f(COMPONENTSIZE, COMPONENTSIZE));
        component.setFillColor(sf::Color(144,238,144)); // Light green color instead of green to differentiate body and head
        this->direction = direction;
    }
    ~SnakeBody() = default;

    sf::RectangleShape getShape() const;
    float getX() const;
    float getY() const;
    sf::Vector2i getDirection() const;
    sf::Vector2i getGridPosition() const;
    sf::Vector2f getPosition() const;

    void setDirection(sf::Vector2i direction);
    void setPosition(float mX, float mY); // For manually giving coordinates
    void setPosition(sf::Vector2f position);
    void setPosition(sf::Vector2i position);

    void update(sf::Vector2i position);
};


#endif //SFML_TEMPLATE_SNAKEBODY_HPP
