#include "iostream"
#include "queue"
#include <SFML/Graphics.hpp>
#include "random"
#include "constants.hpp"
#include "GridCell.hpp"

int BOMBNUMBER = 10, BOARDSIZE = 9;

bool isAllRevealed = false;

// Function to randomly generate bombs across the grid
void generateBombs(std::vector<std::vector<GridCell>> &grid, std::vector<std::vector<sf::Text>> &gridText) {
    // rng engine
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> rowDist(0, BOARDSIZE - 1);
    std::uniform_int_distribution<int> colDist(0, BOARDSIZE - 1);

    // Place bombs randomly in the matrix
    int bombsPlaced = 0;
    while (bombsPlaced < BOMBNUMBER) {
        // generate random rows and columns
        int randomRow = rowDist(gen);
        int randomCol = colDist(gen);

        // Check if the cell is already occupied by a bomb
        if (grid[randomRow][randomCol].isBomb()) {
            continue; // Cell already has a bomb, try again
        }

        // Place the bomb in the cell
        grid[randomRow][randomCol].setBomb(true);
        // set the string to * and also red text
        gridText[randomRow][randomCol].setString("*");
        gridText[randomRow][randomCol].setFillColor(sf::Color::Red);
        // increment bombsPlaced
        bombsPlaced++;
    }
}

// switch statement for changing colors of numbers, and also give
// different string if there are no adjacent bombs (ABBA - easier to test)
void setNumberToText(sf::Text &text, const int &numberOfAdjacentBombs) {
    switch (numberOfAdjacentBombs) {
        case 1:
            text.setFillColor(sf::Color::Blue);
            break;
        case 2:
            text.setFillColor(sf::Color::Green);
            break;
        case 3:
            text.setFillColor(sf::Color::Red);
            break;
        case 4:
            text.setFillColor(sf::Color(2, 0, 122)); // Dark blue
            break;
        case 5:
            text.setFillColor(sf::Color(92, 1, 2)); // Dark red
            break;
        case 6:
            text.setFillColor(sf::Color(12, 207, 194)); // turquoise
            break;
        case 7:
            text.setFillColor(sf::Color::Black);
            break;
        default:
            text.setFillColor(sf::Color(255, 255, 255, 0));
            break;
    }
    // int to string
    std::string temp = std::to_string(numberOfAdjacentBombs);
    if (numberOfAdjacentBombs == 0) {
        temp = "ABBA"; // code for when the cell is surrounded by 0 bombs
    }
    text.setString(temp);
}

// Logic for counting bombs of adjacent cells
void generateNumbers(std::vector<std::vector<GridCell>> &grid, std::vector<std::vector<sf::Text>> &gridText) {
    int numberOfAdjacentBombs = 0;

    for (int i = 0; i < BOARDSIZE; ++i) {
        for (int j = 0; j < BOARDSIZE; ++j) {
            if (!grid[i][j].isBomb()) {
                numberOfAdjacentBombs = 0;
                // Check if cell above is bomb
                if (i != 0 && grid[i - 1][j].isBomb()) {
                    numberOfAdjacentBombs++;
                }
                // Check if cell bellow is bomb
                if (i != BOARDSIZE - 1 && grid[i + 1][j].isBomb()) {
                    numberOfAdjacentBombs++;
                }
                // Check if cell left is bomb
                if (j != 0 && grid[i][j - 1].isBomb()) {
                    numberOfAdjacentBombs++;
                }
                // Check if cell right is bomb
                if (j != BOARDSIZE - 1 && grid[i][j + 1].isBomb()) {
                    numberOfAdjacentBombs++;
                }
                // Check if bomb left above is bomb
                if (i != 0 && j != 0 && grid[i - 1][j - 1].isBomb()) {
                    numberOfAdjacentBombs++;
                }
                // Check if bomb right above is bomb
                if (i != 0 && j != BOARDSIZE - 1 && grid[i - 1][j + 1].isBomb()) {
                    numberOfAdjacentBombs++;
                }
                // Check if bomb left bellow is bomb
                if (i != BOARDSIZE - 1 && j != 0 && grid[i + 1][j - 1].isBomb()) {
                    numberOfAdjacentBombs++;
                }
                // Check if bomb right bellow is bomb
                if (i != BOARDSIZE - 1 && j != BOARDSIZE - 1 && grid[i + 1][j + 1].isBomb()) {
                    numberOfAdjacentBombs++;
                }
                // call function to turn int to string and change colors
                setNumberToText(gridText[i][j], numberOfAdjacentBombs);
            }
        }
    }

}

// draw starting text
void drawStartText(const sf::Text &startGameText, const sf::Text &quitText, const std::vector<sf::Text> &difficultyText,
                   sf::RenderWindow &window) {
    window.draw(startGameText);
    for (int i = 0; i < 3; ++i) {
        window.draw(difficultyText[i]);
    }
    window.draw(quitText);
}

// draw game text and grid cells
void drawGrid(const std::vector<std::vector<GridCell>> &grid, const std::vector<std::vector<sf::Text>> &gridText,
              sf::RenderWindow &window) {
    for (int i = 0; i < BOARDSIZE; ++i) {
        for (int j = 0; j < BOARDSIZE; ++j) {
            window.draw(grid[i][j].getShape());
            if (grid[i][j].isRevealed())
                window.draw(gridText[i][j]);
        }
    }
}

// Recursive algorithm that checks if there are empty cells yet to be revealed and are close together.
void floodFill(std::vector<std::vector<GridCell>> &grid, std::vector<std::vector<sf::Text>> &gridText, int row, int col,
               int first) {
    // Check if the cell is within the grid and not revealed or a bomb
    if ((first == 0) || (row >= 0 && row < BOARDSIZE && col >= 0 && col < BOARDSIZE && !grid[row][col].isRevealed() &&
                         !grid[row][col].isBomb())) {
        // Reveal the cell, and set fill color
        grid[row][col].setFillColor(sf::Color(73, 73, 74));
        grid[row][col].setRevealed(true);

        // temp variable, so that it doesn't need to check revealed state of first cell;
        first = 1;

        // If the cell has no adjacent bombs, call floodFill for its neighbors
        if (gridText[row][col].getString() == "ABBA") {
            floodFill(grid, gridText, row - 1, col, first); // Top
            floodFill(grid, gridText, row + 1, col, first); // Bottom
            floodFill(grid, gridText, row, col - 1, first); // Left
            floodFill(grid, gridText, row, col + 1, first); // Right
        }
    }
}

void revealAll(std::vector<std::vector<GridCell>> &grid) {
    for (int i = 0; i < BOARDSIZE; ++i) {
        for (int j = 0; j < BOARDSIZE; ++j) {
            grid[i][j].setRevealed(true);
            grid[i][j].setFillColor(sf::Color(73, 73, 74));
            isAllRevealed = true;
        }
    }
}

// Every time there is a mouse click event, it checks if it was in cells coordinates
void testPositionMouseCell(std::vector<std::vector<GridCell>> &grid, std::vector<std::vector<sf::Text>> &gridText,
                           sf::Event &gameEvent) {
    for (int i = 0; i < BOARDSIZE; ++i) {
        for (int j = 0; j < BOARDSIZE; ++j) {
            if (grid[i][j].getGlobalBounds().contains(gameEvent.mouseButton.x,
                                                      gameEvent.mouseButton.y)) {
                grid[i][j].setFillColor(sf::Color(73, 73, 74));
                grid[i][j].setRevealed(true);
                //if the cell isn't a bomb and has ABBA set as string, then try other cells around it for floodfill.
                if (!grid[i][j].isBomb() && gridText[i][j].getString() == "ABBA") {
                    floodFill(grid, gridText, i, j, 0);
                }
                if (grid[i][j].isBomb()) {
                    revealAll(grid);
                }
            }
        }
    }
}

// for setting flag cell (just setting fill color to red or back to gray)
void setFlagCell(std::vector<std::vector<GridCell>> &grid, sf::Event &gameEvent) {
    for (int i = 0; i < BOARDSIZE; ++i) {
        for (int j = 0; j < BOARDSIZE; ++j) {
            if (grid[i][j].getGlobalBounds().contains(gameEvent.mouseButton.x,
                                                      gameEvent.mouseButton.y)
                && !grid[i][j].isRevealed()) {
                if (grid[i][j].getFillColor() == sf::Color::Red) {
                    grid[i][j].setFillColor(sf::Color(174, 178, 184));
                } else {
                    grid[i][j].setFillColor(sf::Color::Red);
                }
            }
        }
    }
}

// generating all needed text for start
void generateText(sf::Text &pointsText, sf::Text &startGameText, std::vector<sf::Text> &difficultyText, sf::Text &quitText,
             const sf::Font &font) {
    pointsText.setFont(font);
    pointsText.setString("Points: 0");
    pointsText.setFillColor(sf::Color::White);
    pointsText.setPosition(100, 0);

    startGameText.setFont(font);
    startGameText.setString("Start game");
    startGameText.setCharacterSize(40);
    startGameText.setFillColor(sf::Color::White);
    startGameText.setPosition(820, 285);

    sf::Text easyDiff;
    easyDiff.setFont(font);
    easyDiff.setString("Easy");
    easyDiff.setCharacterSize(26);
    easyDiff.setFillColor(sf::Color(143, 161, 247));
    easyDiff.setPosition(800, 460);

    sf::Text mediumDiff;
    mediumDiff.setFont(font);
    mediumDiff.setString("Medium");
    mediumDiff.setCharacterSize(26);
    mediumDiff.setFillColor(sf::Color(143, 161, 247));
    mediumDiff.setPosition(880, 460);

    sf::Text hardDiff;
    hardDiff.setFont(font);
    hardDiff.setString("Hard");
    hardDiff.setCharacterSize(26);
    hardDiff.setFillColor(sf::Color(143, 161, 247));
    hardDiff.setPosition(1000, 460);

    difficultyText.push_back(easyDiff);
    difficultyText.push_back(mediumDiff);
    difficultyText.push_back(hardDiff);

    quitText.setFont(font);
    quitText.setString("Quit.");
    quitText.setCharacterSize(40);
    quitText.setFillColor(sf::Color::White);
    quitText.setPosition(880, 600);
}

// all difficulty settings
void setDifficulty(std::vector<std::vector<GridCell>> &grid, std::vector<std::vector<sf::Text>> &gridText,
                       const sf::Font &font, char difficultySet) {
    // based on which character, set bomb number and board size
    switch (difficultySet) {
        case 'e':
            BOMBNUMBER = 10, BOARDSIZE = 9;
            break;
        case 'm':
            BOMBNUMBER = 40, BOARDSIZE = 16;
            break;
        case 'h':
            BOMBNUMBER = 99, BOARDSIZE = 24;
            break;
        default:
            BOMBNUMBER = 10, BOARDSIZE = 9;
            break;
    }

    grid.clear();
    gridText.clear();

    // Calculate the total width and height of the grid
    int gridWidth = BOARDSIZE * GRIDSIZE;
    int gridHeight = BOARDSIZE * GRIDSIZE;
    // Calculate the starting position to center the grid
    int startX = (1920 - gridWidth) / 2;
    // if the difficulty is hard, set startY to 0, because the grid is too big on hard diff,
    // the y-axis doesn't need to be in the middle
    int startY = (difficultySet != 'h') ? (1080 - gridHeight) / 2 : 0;

    std::vector<std::vector<GridCell>> tempGrid(BOARDSIZE, std::vector<GridCell>());
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            GridCell cell(startX + i * GRIDSIZE, startY + j * GRIDSIZE);
            tempGrid[i].push_back(cell);
        }
    }
    // set grid to be the same as tempGrid
    grid = tempGrid;

    sf::Text temp;
    temp.setFont(font);
    temp.setString("");
    temp.setCharacterSize(12);
    temp.setFillColor(sf::Color::Magenta);

    float textX = 0;
    float textY = 0;
    std::vector<std::vector<sf::Text>> tempText(BOARDSIZE, std::vector<sf::Text>());
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            textX = startX + i * GRIDSIZE + (GRIDSIZE - temp.getLocalBounds().width) / 2.37f;
            textY = startY + j * GRIDSIZE + (GRIDSIZE - temp.getLocalBounds().height) / 2.7f;
            // set position of text to be in center of cell
            temp.setPosition(textX, textY);
            tempText[i].push_back(temp);
        }
    }
    gridText = tempText;

    generateBombs(grid, gridText);
    generateNumbers(grid, gridText);
}

int main() {
    auto window = sf::RenderWindow{{1920, 1080}, "Minesweeper"};
    window.setFramerateLimit(240);
    sf::Event gameEvent;

    sf::Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

    // create grid and gridText vectors to be filled by functions
    std::vector<std::vector<GridCell>> grid;
    std::vector<std::vector<sf::Text>> gridText;

    // text for starting game menu
    sf::Text pointsText;
    sf::Text startGameText;
    std::vector<sf::Text> difficultyText;
    sf::Text quitText;
    // function for generating all text (except gridText, which is generated based on grid size and bomb number)
    generateText(pointsText, startGameText, difficultyText, quitText, font);

    // Set easy diff for first start
    setDifficulty(grid, gridText, font, 'e');

    // boolean for starting game
    bool gameStart = false;
    // Game loop - runs every frame
    while (window.isOpen()) {
        window.clear();
        while (!gameStart) {
            window.clear();
            // check if esc is pressed, close window
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            // if there was an event
            while (window.pollEvent(gameEvent)) {
                if (gameEvent.type == sf::Event::Closed) { // if event is window closed
                    window.close();
                }
                    // if left mouse button was pressed
                else if (gameEvent.mouseButton.button == sf::Mouse::Left) {
                    // in every if, check the global bounds (coordinates) of text and if the mouse is within those bounds
                    if (startGameText.getGlobalBounds().contains(gameEvent.mouseButton.x, gameEvent.mouseButton.y)) {
                        gameStart = true;
                    } else if (quitText.getGlobalBounds().contains(gameEvent.mouseButton.x, gameEvent.mouseButton.y)) {
                        window.close();
                    }
                        // setting difficulty easy, medium, hard
                    else if (difficultyText[0].getGlobalBounds().contains(gameEvent.mouseButton.x,
                                                                          gameEvent.mouseButton.y)) {
                        setDifficulty(grid, gridText, font, 'e');
                    } else if (difficultyText[1].getGlobalBounds().contains(gameEvent.mouseButton.x,
                                                                            gameEvent.mouseButton.y)) {
                        setDifficulty(grid, gridText, font, 'm');
                    } else if (difficultyText[2].getGlobalBounds().contains(gameEvent.mouseButton.x,
                                                                            gameEvent.mouseButton.y)) {
                        setDifficulty(grid, gridText, font, 'h');
                    }
                }
            }
            // draw all starting text
            drawStartText(startGameText, quitText, difficultyText, window);
            window.display();
        }
        while (gameStart) {
            window.clear();
            // if esc was pressed go back to start
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                gameStart = false;
            }
            while (window.pollEvent(gameEvent)) {
                // if left mouse button was pressed, call function to check if it was in a cell, and then do all
                // the necessary things
                if (gameEvent.mouseButton.button == sf::Mouse::Left) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        testPositionMouseCell(grid, gridText, gameEvent);
                    }
                } else if (gameEvent.mouseButton.button == sf::Mouse::Right) { // same for flag but right mouse button
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                        setFlagCell(grid, gameEvent);
                    }
                }
            }

            // draws grid and gridText that isn't yet shown if it is not revealed
            drawGrid(grid, gridText, window);
            window.display(); // Draws to window
        }
    }
}