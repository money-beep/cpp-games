#include "iostream"
#include "string"
#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "Platform.hpp"

constexpr int WIDTHWINDOW = 1480, HEIGHTWINDOW = 900;

void makePointText(sf::Text &playerOnePoints, sf::Text &playerTwoPoints, sf::Font &font){
    playerOnePoints.setFont(font);
    playerOnePoints.setString("0");
    playerOnePoints.setCharacterSize(100);
    playerOnePoints.setFillColor(sf::Color::White);
    playerOnePoints.setPosition(650, 50);

    playerTwoPoints.setFont(font);
    playerTwoPoints.setString("0");
    playerTwoPoints.setCharacterSize(100);
    playerTwoPoints.setFillColor(sf::Color::White);
    playerTwoPoints.setPosition(780, 50);
}

void checkForGoal(Ball &bounceBall, sf::Text &playerOnePoints, sf::Text &playerTwoPoints){
    // from sf::Text to string
    std::string playerOneString = playerOnePoints.getString();
    std::string playerTwoString = playerTwoPoints.getString();

    // from string to int
    int playerOneIntPoints = std::stoi( playerOneString);
    int playerTwoIntPoints = std::stoi(playerTwoString);

    if(bounceBall.getX() > 1480){
        playerOneIntPoints++;
        bounceBall.setX(WIDTHWINDOW/2);
    }
    if(bounceBall.getX() < 0){
        playerTwoIntPoints++;
        bounceBall.setX(WIDTHWINDOW/2);
    }

    playerOnePoints.setString(std::to_string(playerOneIntPoints));
    playerTwoPoints.setString(std::to_string(playerTwoIntPoints));
}


void drawObjects(sf::RenderWindow &window, const Platform &platformLeft, const Platform &platformRight, const Ball &bounceBall, const std::vector<sf::RectangleShape> &squareLine, const sf::Text &playerOne, const sf::Text &playerTwo){
    window.draw(platformLeft.getShape());
    window.draw(platformRight.getShape());
    window.draw(bounceBall.getShape());
    window.draw(playerOne);
    window.draw(playerTwo);
    for (const auto &square : squareLine) {
        window.draw(square);
    }
    window.display();
}

std::vector<sf::RectangleShape> makeSquares(){
    std::vector<sf::RectangleShape> tempVector;

    int squareSize = 15;
    int numSquares = 25;
    int verticalSpacing = (HEIGHTWINDOW - numSquares * squareSize) / (numSquares + 1);

    int x = (WIDTHWINDOW - squareSize) / 2, y = 0;
    for(int i = 0; i < numSquares; i++){
        y = verticalSpacing * (i + 1) + squareSize * i;
        sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
        square.setPosition(x, y);
        square.setFillColor(sf::Color::White);
        tempVector.push_back(square);
    }

    return tempVector;
}

template<class T1, class T2>
bool isColliding(T1 &shapeA, T2 &shapeB) {
    return shapeA.maxRight() >= shapeB.maxLeft() && shapeA.maxLeft() <= shapeB.maxRight()
           && shapeA.maxBottom() >= shapeB.maxTop() && shapeA.maxTop() <= shapeB.maxBottom();
}

void testCollisionPlayerPlatform(Platform &platform, Ball &ball) {
    if (!isColliding(platform, ball)) {
        return;
    }

    float platformAreaOfImpact = (ball.getY() - platform.getY()) / platform.getHeight();
    std::cout << "AREA OF IMPACT: " << platformAreaOfImpact << "\n";

    if(platformAreaOfImpact < -0.1f){
        ball.bounceDiagonally(true);
    } else if (platformAreaOfImpact > 0.1f){
        ball.bounceDiagonally(false);
    } else {
        ball.bounceHorizontally();
    }
}

void testAndUpdateObjects(Platform &platformLeft, Platform &platformRight, Ball &bounceBall, sf::Text &playerOnePoints, sf::Text &playerTwoPoints){
    testCollisionPlayerPlatform(platformLeft, bounceBall);
    testCollisionPlayerPlatform(platformRight, bounceBall);
    checkForGoal(bounceBall, playerOnePoints, playerTwoPoints);

    platformLeft.update();
    platformRight.update();
    bounceBall.update();
}

int main() {
    auto window = sf::RenderWindow{{WIDTHWINDOW, HEIGHTWINDOW}, "Pong - clone"};
    window.setFramerateLimit(240);
    sf::Event gameEvent;

    sf::Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
    sf::Text playerOnePoints, playerTwoPoints;
    makePointText(playerOnePoints, playerTwoPoints, font);

    Platform platformLeft(25, HEIGHTWINDOW/2, sf::Keyboard::W, sf::Keyboard::S);
    Platform platformRight(WIDTHWINDOW-25, HEIGHTWINDOW/2, sf::Keyboard::Up, sf::Keyboard::Down);
    Ball bounceBall(WIDTHWINDOW/2, HEIGHTWINDOW/2);

    std::vector<sf::RectangleShape> squareLine;
    squareLine = makeSquares();

    // Game loop - runs every frame
    while (window.isOpen()) {
        window.clear();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        // check for events
        while (window.pollEvent(gameEvent)) {  // if event is a key press
            if (gameEvent.type == sf::Event::Closed) { // if event is window closed
                window.close();
            }
        }
        testAndUpdateObjects(platformLeft, platformRight, bounceBall, playerOnePoints, playerTwoPoints);
        drawObjects(window, platformLeft, platformRight, bounceBall, squareLine, playerOnePoints, playerTwoPoints);
    }
}