#include "iostream"
#include <SFML/Graphics.hpp>
#include "constants.hpp"

int main() {
    auto window = sf::RenderWindow{{WIDTHWINDOW, HEIGHTWINDOW}, "Minesweeper"};
    window.setFramerateLimit(240);
    sf::Event gameEvent;

    sf::RectangleShape gridCell;
    gridCell.setSize(sf::Vector2f(GRIDSIZE, GRIDSIZE));
    gridCell.setPosition(0,0);
    gridCell.setFillColor(sf::Color::Green);
    gridCell.setOutlineThickness(0.1);
    gridCell.setOutlineColor(sf::Color::Blue);

    sf::RectangleShape grid[9][9];
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            grid[i][j] = gridCell;
            gridCell.setPosition(gridCell.getPosition().x + GRIDSIZE, gridCell.getPosition().y);
        }
        gridCell.setPosition(0, gridCell.getPosition().y + GRIDSIZE);
    }

    //window.setSize(sf::Vector2u(1060,1060)); Use this function to change size of window based on selected difficulty

    // Game loop - runs every frame
    while (window.isOpen()) {
        window.clear();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        while(window.pollEvent(gameEvent)){
            if (gameEvent.type == sf::Event::Closed) { // if event is window closed
                window.close();
            }
        }

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                window.draw(grid[i][j]);
            }
        }
        window.display(); // Draws to window
    }
}