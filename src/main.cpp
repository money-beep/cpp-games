#include "iostream"
#include <SFML/Graphics.hpp>
#include "SnakeHead.hpp"
#include "SnakeBody.hpp"
#include "constants.hpp"

void testCollisionSnake(SnakeHead &snake) {
    if (snake.getX() > 800) {
        snake.setPosition(0, snake.getY());
    }
    if (snake.getX() < 0) {
        snake.setPosition(800, snake.getY());
    }
    if (snake.getY() > 600) {
        snake.setPosition(snake.getX(), 0);
    }
    if (snake.getY() < 0) {
        snake.setPosition(snake.getX(), 600);
    }
}

void updateSnakeBodyPosition(std::vector<sf::Vector2i> &snakeBodyPartPosition, std::vector<SnakeBody> &snakeBody, sf::Vector2i lastMoveDirection){
    sf::Vector2i tempDirection;
    for (int i = 0; i < snakeBodyPartPosition.size(); ++i) {
        if(i == 0 || i % 2 == 0) {
            tempDirection = snakeBody[i].getDirection();
            snakeBodyPartPosition[i] += snakeBody[i].getDirection();
            snakeBody[i].setDirection(lastMoveDirection);
        } else {
            lastMoveDirection = snakeBody[i].getDirection();
            snakeBodyPartPosition[i] += snakeBody[i].getDirection();
            snakeBody[i].setDirection(tempDirection);
        }
    }
}

int main() {
    auto window = sf::RenderWindow{{800, 600}, "Snake game"};
    window.setFramerateLimit(240);
    sf::Event gameEvent;
    sf::Clock clock;

    SnakeHead snakeHead(2, 2); // Coordinates of grid
    sf::Vector2i snakeHeadPosition(snakeHead.getPosition().x / GRIDSIZE, snakeHead.getPosition().y / GRIDSIZE); // position needs to be divided by grid size to represent grid block.

    SnakeBody snakeBodyPart(1, 2);
    std::vector<SnakeBody> snakeBody;
    std::vector<sf::Vector2i> snakeBodyPartPosition;
    for (int i = 0; i < 2; i++) { // start from 1 to immediately start counting up
        snakeBody.push_back(snakeBodyPart);
        snakeBodyPartPosition.push_back(snakeBodyPart.getGridPosition());
        snakeBodyPart.setPosition(0, 2);
    }

    sf::Vector2i firstBodyPartDirection(snakeHead.getDirection());
    // Game loop - runs every frame
    while (window.isOpen()) {
        window.clear();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        while (window.pollEvent(gameEvent)) {  // if event is a key press
            if (gameEvent.type == sf::Event::Closed) { // if event is window closed
                window.close();
            }
        }

        if (clock.getElapsedTime().asMilliseconds() >= 100) {
            snakeHeadPosition += snakeHead.getDirection();
            snakeHead.updatePosition(snakeHeadPosition);
            testCollisionSnake(snakeHead);
            updateSnakeBodyPosition(snakeBodyPartPosition, snakeBody,snakeHead.getLastMoveDirection());
            clock.restart();
        }
        snakeHead.updateDirection();

        //updateSnakeBody(snakeBody, snakeHead.getDirection(), snakeBodyPartPosition);
        for (int i = 0; i < snakeBody.size(); i++) {
            snakeBody[i].update(snakeBodyPartPosition[i]);
        }
        for(const auto &part : snakeBody){
            window.draw(part.getShape());
        }
        window.draw(snakeHead.getShape());
        window.display();
    }
}