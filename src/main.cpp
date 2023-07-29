#include "iostream"
#include <SFML/Graphics.hpp>
#include "SnakeHead.hpp"
#include "SnakeBody.hpp"
#include "Apple.hpp"
#include "constants.hpp"

void testCollisionSnake(SnakeHead &snake) {
    sf::Vector2i position = snake.getGridPosition();
    if (position.x < 0)
        snake.setPosition(780, snake.getY());
    if (position.x >= WIDTHGRID)
        snake.setPosition(0, snake.getY());
    if (position.y < 0)
        snake.setPosition(snake.getX(), 580);
    if (position.y >= HEIGHTGRID)
        snake.setPosition(snake.getX(), 0);
}

void testCollisionAppleSnake(sf::Vector2i snakeHead, std::vector<SnakeBody> &snakeBody, std::vector<sf::Vector2i> &snakeBodyPartPosition, Apple &apple, int &points){
    if(snakeHead == apple.getGridPosition()){
        // Adding a part to snake's body
        sf::Vector2i positionPart = snakeBody[snakeBody.size()-1].getGridPosition();
        sf::Vector2i directionPart = snakeBody[snakeBody.size()-1].getDirection();
        // Add to the opposite direction of where the last part was supposed to move
        // so that the added part can be placed behind it.
        positionPart -= directionPart;
        SnakeBody tempSnakePart(positionPart.x, positionPart.y, directionPart);
        snakeBody.push_back(tempSnakePart);
        // Adding a position vector to body part position
        snakeBodyPartPosition.push_back(positionPart);
        //Calling apple function to re-randomize position
        apple.randomize();
        points += 10;
    }
}

void updateSnakeBodyPosition(std::vector<sf::Vector2i> &snakeBodyPartPosition, std::vector<SnakeBody> &snakeBody, sf::Vector2i lastMoveDirection){
    sf::Vector2i tempDirection;
    for (int i = 0; i < snakeBodyPartPosition.size(); ++i) {
        if(i == 0 || i % 2 == 0) {
            // get direction of where body part needs to go
            tempDirection = snakeBody[i].getDirection();
            // add the direction (+1 or -1 in some direction) because the vector is (x, y) and the direction can only
            // have one VALUE in either x or y
            snakeBodyPartPosition[i] += snakeBody[i].getDirection();
            // setting the position
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

    SnakeBody snakeBodyPart(1, 2, sf::Vector2i(1, 0));
    std::vector<SnakeBody> snakeBody;
    std::vector<sf::Vector2i> snakeBodyPartPosition;
    for (int i = 0; i < 2; i++) { // start from 1 to immediately start counting up
        snakeBody.push_back(snakeBodyPart);
        snakeBodyPartPosition.push_back(snakeBodyPart.getGridPosition());
        snakeBodyPart.setPosition(0, 2);
    }
    sf::Vector2i firstBodyPartDirection(snakeHead.getDirection());

    Apple apple;

    bool gameStarted = false;
    // Generating starting menu
    sf::Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

    int points = 0;
    sf::Text pointsText;
    pointsText.setFont(font);
    pointsText.setString("Points: 0");
    pointsText.setScale(0.75f, 0.75f);
    pointsText.setFillColor(sf::Color::White);
    pointsText.setPosition(600, 0);

    sf::Text startGameText;
    startGameText.setFont(font);
    startGameText.setString("Start game");
    startGameText.setScale(1.5f, 1.5f);
    startGameText.setFillColor(sf::Color::White);
    startGameText.setPosition(300, 100);

    sf::Text quitText;
    quitText.setFont(font);
    quitText.setString("Quit.");
    quitText.setScale(1.2f, 1.2f);
    quitText.setFillColor(sf::Color::White);
    quitText.setPosition(360, 250);
    // Game loop - runs every frame
    while (window.isOpen()) {
        while(!gameStarted){
            window.clear(sf::Color::Black);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            // check for events
            while (window.pollEvent(gameEvent)) {  // if event is a key press
                if (gameEvent.type == sf::Event::Closed) { // if event is window closed
                    window.close();
                }
                else if( gameEvent.mouseButton.button == sf::Mouse::Left){
                    if(startGameText.getGlobalBounds().contains(gameEvent.mouseButton.x, gameEvent.mouseButton.y)){
                        gameStarted = true;
                    } else if(quitText.getGlobalBounds().contains(gameEvent.mouseButton.x, gameEvent.mouseButton.y)){
                        window.close();
                    }
                }
            }
            window.draw(startGameText);
            window.draw(quitText);
            window.display();
        }
        clock.restart();
        while(gameStarted) {
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
                testCollisionAppleSnake(snakeHeadPosition, snakeBody, snakeBodyPartPosition, apple, points);
                testCollisionSnake(snakeHead);
                updateSnakeBodyPosition(snakeBodyPartPosition, snakeBody, snakeHead.getLastMoveDirection());
                clock.restart();
            }
            snakeHead.updateDirection();

            //updateSnakeBody(snakeBody, snakeHead.getDirection(), snakeBodyPartPosition);
            for (int i = 0; i < snakeBody.size(); i++) {
                snakeBody[i].update(snakeBodyPartPosition[i]);
            }
            for (const auto &part: snakeBody) {
                window.draw(part.getShape());
            }
            window.draw(apple.getShape());
            window.draw(snakeHead.getShape());

            pointsText.setString("Points: " + std::to_string(points));
            window.draw(pointsText);
            window.display();
        }
    }
}