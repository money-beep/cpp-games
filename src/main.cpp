#include "iostream"
#include <SFML/Graphics.hpp>
#include "random"
#include "constants.hpp"
#include "GridCell.hpp"

// Function to randomly generate bombs across the grid
void generateBombs(std::vector<std::vector<GridCell>> &grid, std::vector<std::vector<sf::Text>> &gridText, const int numberOfBombs) {
    // rng engine
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> rowDist(0, 9 - 1);
    std::uniform_int_distribution<int> colDist(0, 9 - 1);

    // Place bombs randomly in the matrix
    int bombsPlaced = 0;
    while (bombsPlaced < numberOfBombs) {
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
void setNumberToText(sf::Text &text, const int &numberOfAdjacentBombs){
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
            text.setFillColor(sf::Color(255,255,255,0));
            break;
    }
    // int to string
    std::string temp = std::to_string(numberOfAdjacentBombs);
    if(numberOfAdjacentBombs == 0){
        temp = "ABBA";
    }
    text.setString(temp);
}

// Logic for counting bombs of adjacent cells
void generateNumbers(std::vector<std::vector<GridCell>> &grid, std::vector<std::vector<sf::Text>> &gridText) {
    int numberOfAdjacentBombs = 0;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (!grid[i][j].isBomb()) {
                numberOfAdjacentBombs = 0;
                // Check if cell above is bomb
                if (i != 0 && grid[i - 1][j].isBomb()) {
                    numberOfAdjacentBombs++;
                }
                // Check if cell bellow is bomb
                if (i != 8 && grid[i + 1][j].isBomb()) {
                    numberOfAdjacentBombs++;
                }
                // Check if cell left is bomb
                if (j != 0 && grid[i][j - 1].isBomb()) {
                    numberOfAdjacentBombs++;
                }
                // Check if cell right is bomb
                if (j != 8 && grid[i][j + 1].isBomb()) {
                    numberOfAdjacentBombs++;
                }
                // Check if bomb left above is bomb
                if (i != 0 && j != 0 && grid[i - 1][j - 1].isBomb()) {
                    numberOfAdjacentBombs++;
                }
                // Check if bomb right above is bomb
                if (i != 0 && j != 8 && grid[i - 1][j + 1].isBomb()) {
                    numberOfAdjacentBombs++;
                }
                // Check if bomb left bellow is bomb
                if(i != 8 && j != 0 && grid[i+1][j-1].isBomb()){
                    numberOfAdjacentBombs++;
                }
                // Check if bomb right bellow is bomb
                if(i != 8 && j != 8 && grid[i+1][j+1].isBomb()){
                    numberOfAdjacentBombs++;
                }
                // call function to turn int to string and change colors
                setNumberToText(gridText[i][j], numberOfAdjacentBombs);
            }
        }
    }

}

// draw text and cells
void drawGrid(const std::vector<std::vector<GridCell>> &grid, const std::vector<std::vector<sf::Text>> &gridText, sf::RenderWindow &window) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            window.draw(grid[i][j].getShape());
            if (grid[i][j].isRevealed())
                window.draw(gridText[i][j]);
        }
    }
}

// Recursive algorithm that checks if there are empty cells yet to be revealed and are close together.
void floodFill(std::vector<std::vector<GridCell>> &grid, std::vector<std::vector<sf::Text>> &gridText, const int row, const int col, int first) {
    // Check if the cell is within the grid and not revealed or a bomb
    if ((first == 0) || (row >= 0 && row < 9 && col >= 0 && col < 9 && !grid[row][col].isRevealed() && !grid[row][col].isBomb())) {
        // Reveal the cell, and set fill color
        grid[row][col].setFillColor(sf::Color(73, 73, 74));
        grid[row][col].setRevealed(true);

        // temp variable, so that it doesn't need to check revealed state of first cell;
        first = 1;

        // If the cell has no adjacent bombs, call floodFill for its neighbors
        if (gridText[row][col].getString() == "ABBA") {
            floodFill(grid, gridText,row - 1, col, first); // Top
            floodFill(grid, gridText,row + 1, col, first); // Bottom
            floodFill(grid, gridText, row, col - 1, first); // Left
            floodFill(grid, gridText, row, col + 1, first); // Right
        }
    }
}

// Every time there is a mouse click event, it checks if it was in cells coordinates
void testPositionMouseCell(std::vector<std::vector<GridCell>> &grid, std::vector<std::vector<sf::Text>> &gridText,sf::Event &gameEvent) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (grid[i][j].getGlobalBounds().contains(gameEvent.mouseButton.x,
                                                      gameEvent.mouseButton.y)) {
                grid[i][j].setFillColor(sf::Color(73, 73, 74));
                grid[i][j].setRevealed(true);
                //if the cell isn't a bomb and has ABBA set as string, then try other cells around it for floodfill.
                if (!grid[i][j].isBomb() && gridText[i][j].getString() == "ABBA") {
                    floodFill(grid, gridText, i, j, 0);
                }
            }
        }
    }
}

void setFlagCell(std::vector<std::vector<GridCell>> &grid, sf::Event &gameEvent){
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (grid[i][j].getGlobalBounds().contains(gameEvent.mouseButton.x,
                                                      gameEvent.mouseButton.y)
                                                      && !grid[i][j].isRevealed()) {
                if(grid[i][j].getFillColor() == sf::Color::Red){
                    grid[i][j].setFillColor(sf::Color(174, 178, 184));
                } else {
                    grid[i][j].setFillColor(sf::Color::Red);
                }
            }
        }
    }
}

int main() {
    auto window = sf::RenderWindow{{WIDTHWINDOW, HEIGHTWINDOW}, "Minesweeper"};
    window.setFramerateLimit(240);
    sf::Event gameEvent;

    sf::Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

    std::vector<std::vector<GridCell>> grid(9, std::vector<GridCell>());
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            GridCell cell(i, j);
            grid[i].push_back(cell);
        }
    }

    sf::Text tempText;
    tempText.setFont(font);
    tempText.setString("");
    tempText.setCharacterSize(12);
    tempText.setFillColor(sf::Color::Magenta);

    float textX = 0;
    float textY = 0;
    std::vector<std::vector<sf::Text>> gridText(9, std::vector<sf::Text>());
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            textX = i * GRIDSIZE + (GRIDSIZE - tempText.getLocalBounds().width) / 2.37f;
            textY = j * GRIDSIZE + (GRIDSIZE - tempText.getLocalBounds().height) / 2.7f;
            // set position of text to be in center of cell
            tempText.setPosition(textX, textY);
            gridText[i].push_back(tempText);
        }
    }

    int numberOfBombs = 9;

    generateBombs(grid, gridText,numberOfBombs);
    generateNumbers(grid, gridText);
    //window.setSize(sf::Vector2u(1060,1060)); Use this function to change size of window based on selected difficulty

    // Game loop - runs every frame
    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        while (window.pollEvent(gameEvent)) {
            if (gameEvent.type == sf::Event::Closed) { // if event is window closed
                window.close();
            } else if (gameEvent.mouseButton.button == sf::Mouse::Left) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    testPositionMouseCell(grid, gridText, gameEvent);
                }
            } else if(gameEvent.mouseButton.button == sf::Mouse::Right){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                    setFlagCell(grid, gameEvent);
                }
            }
        }

        //window.draw(grid[0][4].getText());
        drawGrid(grid, gridText, window);
        window.display(); // Draws to window
    }
}