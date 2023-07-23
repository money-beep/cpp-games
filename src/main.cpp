#include "iostream"
#include <SFML/Graphics.hpp>
#include "constants.hpp"

int main() {
    auto window = sf::RenderWindow{{WIDTHWINDOW, HEIGHTWINDOW}, "Minesweeper"};
    window.setFramerateLimit(240);
    sf::Event gameEvent;

    window.setSize(sf::Vector2u(1060,1060));

    // Game loop - runs every frame
    while (window.isOpen()) {
        window.display(); // Draws to window
    }
}