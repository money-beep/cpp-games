#ifndef SFML_TEMPLATE_PLATFORM_HPP
#define SFML_TEMPLATE_PLATFORM_HPP
#include <SFML/Graphics.hpp>

constexpr int PLATFORMWIDTH = 50, PLATFORMHEIGHT = 10;
constexpr float PLATFORMVELOCITY = 2.f;

class Platform {
private:
    sf::RectangleShape rectangle;
    sf::Vector2f velocity{-PLATFORMVELOCITY, 0};
public:
    Platform(float mX, float mY){
        rectangle.setPosition(mX, mY);
        rectangle.setSize(sf::Vector2f(PLATFORMWIDTH,PLATFORMHEIGHT));
        rectangle.setFillColor(sf::Color::Green);
        rectangle.setOrigin(PLATFORMWIDTH / 2.f, PLATFORMHEIGHT / 2.f);
    }
    ~Platform() = default;

    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    sf::RectangleShape getShape();

    float getX();
    float getY();
    float maxLeft();
    float maxRight();
    float maxTop();
    float maxBottom();

    void update();
};

#endif //SFML_TEMPLATE_PLATFORM_HPP
