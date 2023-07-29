#ifndef SFML_TEMPLATE_PLATFORM_HPP
#define SFML_TEMPLATE_PLATFORM_HPP
#include "SFML/Graphics.hpp"

const float PLATFORMVELOCITY = 2.f;

class Platform {
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;

    sf::Keyboard::Key bindUp, bindDown;
public:
    Platform(float mX, float  mY, sf::Keyboard::Key up, sf::Keyboard::Key down){
        shape.setPosition(mX, mY);
        shape.setSize(sf::Vector2f(20,125));
        shape.setOrigin(shape.getSize() / 2.0f);
        shape.setFillColor(sf::Color::White);
        bindUp = up;
        bindDown = down;
    }

    sf::RectangleShape getShape() const;

    float getHeight() const;

    float getX() const;
    float getY() const;

    float maxLeft();
    float maxRight();
    float maxTop();
    float maxBottom();

    void update();
};


#endif //SFML_TEMPLATE_PLATFORM_HPP
