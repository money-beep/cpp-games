#ifndef SFML_TEMPLATE_BALL_HPP
#define SFML_TEMPLATE_BALL_HPP
#include <SFML/Graphics.hpp>

constexpr float BALLRADIUS = 10.f, BALLVELOCITY = 1.5f;

class Ball {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity{-BALLVELOCITY, -BALLVELOCITY};
public:
    Ball(float mX, float mY){
        shape.setPosition(mX, mY);
        shape.setRadius(BALLRADIUS);
        shape.setFillColor(sf::Color::Red);
        shape.setOrigin(BALLRADIUS,BALLRADIUS);
    }
    ~Ball() = default;

    // for collision
    sf::Vector2f getPosition();
    float getRadius();
    sf::CircleShape getShape();

    // limit ball movement from escaping the window
    float getX();
    float getY();
    float maxLeft();
    float maxRight();
    float maxTop();
    float maxBottom();

    void bounceBall(); // if it touches the player platform
    void setXVelocity(bool position);
    void setYVelocity(bool position);

    void update();
};

#endif //SFML_TEMPLATE_BALL_HPP
