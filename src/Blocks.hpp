#ifndef SFML_TEMPLATE_BLOCKS_HPP
#define SFML_TEMPLATE_BLOCKS_HPP

#include "SFML/Graphics.hpp"

constexpr int BLOCKWIDTH = 70, BLOCKHEIGHT = 30;

class Blocks {
private:
    sf::RectangleShape block;
    bool destroyed = false;
public:
    Blocks(float mX, float mY){
        block.setPosition(mX,mY);
        block.setSize(sf::Vector2f(BLOCKWIDTH, BLOCKHEIGHT));
        block.setOutlineColor(sf::Color::Blue);
        block.setOutlineThickness(0.5f);
        block.setFillColor(sf::Color::Magenta);
        block.setOrigin(BLOCKWIDTH/2.f, BLOCKHEIGHT/2.f);
    }

    sf::RectangleShape getShape() const;
    void setPosition(float mX, float mY);

    float getX() const;
    float getY() const;
    float maxLeft();
    float maxRight();
    float maxTop();
    float maxBottom();

    void setDestroyed();
    bool isDestroyed() const;
};
#endif //SFML_TEMPLATE_BLOCKS_HPP
