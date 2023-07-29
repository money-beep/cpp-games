#ifndef SFML_TEMPLATE_BALL_HPP
#define SFML_TEMPLATE_BALL_HPP
#include "SFML/Graphics.hpp"

const float BALLVELOCITY = 2.25f;

class Ball {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
public:
    Ball(float mX, float mY){
        shape.setPosition(mX, mY);
        shape.setRadius(10.f);
        velocity.x = BALLVELOCITY;
        velocity.y = BALLVELOCITY;
    }

    void setX(float mX);

    sf::CircleShape getShape() const;
    float getX() const;
    float getY() const;

    float maxLeft();
    float maxRight();
    float maxTop();
    float maxBottom();

    void bounceHorizontally();
    void bounceDiagonally(bool direction); // Bool to determine if player platform was hit on top or bottom of corner

    void update();
};


#endif //SFML_TEMPLATE_BALL_HPP
