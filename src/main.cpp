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



    // Game loop - runs every frame
    while (window.isOpen()) {

    }
}