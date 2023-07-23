#ifndef SFML_TEMPLATE_GRIDCELL_HPP
#define SFML_TEMPLATE_GRIDCELL_HPP

#include "SFML/Graphics.hpp"
#include "constants.hpp"

class GridCell {
private:
    sf::RectangleShape cell;
    bool revealed;
    bool bomb;
public:
    GridCell(int mX, int mY){
        cell.setPosition(mX * GRIDSIZE, mY * GRIDSIZE);
        cell.setSize(sf::Vector2f(GRIDSIZE-1, GRIDSIZE-1));
        cell.setFillColor(sf::Color(174, 178, 184));

        revealed = false;
        bomb = false;
    }

    sf::Rect<float> getGlobalBounds() const;
    sf::RectangleShape getShape() const;
    sf::Color getFillColor() const;

    bool isBomb() const;
    bool isRevealed() const;

    void setFillColor(sf::Color color);
    void setBomb(bool bomb);
    void setRevealed(bool revealed);
};


#endif //SFML_TEMPLATE_GRIDCELL_HPP
