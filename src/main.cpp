#include "iostream"
#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "Platform.hpp"
#include "Blocks.hpp"

constexpr int WIDTHWINDOW = 800, HEIGHTWINDOW = 600;

template<class T1, class T2>
bool isColliding(T1 &shapeA, T2 &shapeB) {
    return shapeA.maxRight() >= shapeB.maxLeft() && shapeA.maxLeft() <= shapeB.maxRight()
           && shapeA.maxBottom() >= shapeB.maxTop() && shapeA.maxTop() <= shapeB.maxBottom();
}

void testCollisionPlayerPlatform(Platform &platform, Ball &ball) {
    if (!isColliding(platform, ball)) {
        return;
    }
    ball.bounceBall();
    if (ball.getX() < platform.getX()) {
        ball.setXVelocity(true);
    } else {
        ball.setXVelocity(false);
    }
    if (ball.getY() < platform.getY()) {
        ball.setYVelocity(true);
    } else {
        ball.setYVelocity(false);
    }
}

std::vector<int>  ahah;

void testCollisionBricks(Blocks &block, Ball &ball) {
    if (!isColliding(block, ball)) {
        return;
    }
    ball.bounceBall();
    block.setDestroyed();
    if (ball.getX() < block.getX()) {
        ball.setXVelocity(true);
    } else {
        ball.setXVelocity(false);
    }
    if (ball.getY() < block.getY()) {
        ball.setYVelocity(true);
    } else {
        ball.setYVelocity(false);
    }
}

int main() {
    auto window = sf::RenderWindow{{WIDTHWINDOW, HEIGHTWINDOW}, "Arkanoid-clone"};
    window.setFramerateLimit(240);
    sf::Event gameEvent;

    // Generate game objects (player platform, ball and blocks)
    Ball balls(WIDTHWINDOW / 2, HEIGHTWINDOW / 2);
    Platform platform(WIDTHWINDOW / 2 - 25, HEIGHTWINDOW / 2 + 100);

    std::vector<Blocks> blocks;
    float blockPositionDifferenceX = 80;
    float blockPositionDifferenceY = 50;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            blocks.emplace_back(blockPositionDifferenceX, blockPositionDifferenceY);
            blockPositionDifferenceX += 80;
        }
        blockPositionDifferenceY += 40;
        blockPositionDifferenceX = 80;
    }
    // boolean variable to save game state (if game has started or only in menu)
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
            // Clears window
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

        while(gameStarted) {
            // Clears window
            window.clear(sf::Color::Black);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            // check for events
            while (window.pollEvent(gameEvent)) {  // if event is a key press
                if (gameEvent.type == sf::Event::Closed) { // if event is window closed
                    window.close();
                }
            }
            testCollisionPlayerPlatform(platform, balls);
            for (auto &block: blocks) {
                testCollisionBricks(block, balls);
            }
            balls.update();
            platform.update();
            window.draw(balls.getShape());
            window.draw(platform.getShape());

            blocks.erase(std::remove_if(blocks.begin(), blocks.end(), [&points](Blocks block) {
                if(block.isDestroyed()){
                    points += 10;
                    return true;
                }
                return false;
            }), blocks.end());

            if(blocks.empty()){
                gameStarted = false;
            }

            for (auto &block: blocks) {
                window.draw(block.getShape());
            }

            pointsText.setString("Points: " + std::to_string(points));
            window.draw(pointsText);
            window.display(); // Draws to window
        }
    }
}