#ifndef SFML_TEMPLATE_APPLE_HPP
#define SFML_TEMPLATE_APPLE_HPP
#include "SFML/Graphics.hpp"
#include "random"
#include "constants.hpp"

constexpr float APPLESIZE = 10;

class Apple {
private:
    sf::CircleShape component;
public:
    Apple(){
        std::random_device rd; // non-deterministic random number generator (RNG)
        std::mt19937 gen(rd()); // pseudo-random number generator (PRNG) that uses the Mersenne Twister algorithm. The name "mt19937" stands for "Mersenne Twister 19937."
        // PRNGs generate sequences of numbers that appear to be random but are actually deterministic.
        // The sequence of numbers is generated based on a specific initial state (seed, which is in this case RNG)
        std::uniform_int_distribution<> xDistribution(0, WIDTHGRID - 1); // Generate integers in range of 0 to 39
        std::uniform_int_distribution<> yDistribution(0, HEIGHTGRID - 1); // range of 0 to 29

        int x = xDistribution(gen) * GRIDSIZE; // multiply by blockSize to get the actual position
        int y = yDistribution(gen) * GRIDSIZE;

        component.setRadius(GRIDSIZE / 2.0f);
        component.setFillColor(sf::Color::Red);
        component.setPosition(x, y);
    }

    sf::CircleShape getShape() const;
    sf::Vector2i getGridPosition() const;

    void randomize();

};


#endif //SFML_TEMPLATE_APPLE_HPP
