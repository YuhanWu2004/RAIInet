#include "graphicalobserver.h"
using namespace std;

GraphicalObserver ::GraphicalObserver(Board *myBoard, Player *current_player, Player *opponent, std::map<Position, Cell> &grid,
     Xwindow *window, int max_row, int max_col):
     myBoard{myBoard}, current_player{current_player}, opponent{opponent}, grid{grid}, window{window},
     max_row{max_row}, max_col{max_col}
   {
    myBoard->attach(this);

    }
GraphicalObserver::~GraphicalObserver() {
    // the observer is not responsible for deleting the subject
    myBoard->detach(this);
}

Player *GraphicalObserver::getPlayer() const {return current_player;}

int GraphicalObserver::convertCharacterToColor(char c) {
    if (c >= 'a' && c <= 'h') {
        return Xwindow::Orange;
    }
    if (c >= 'A' && c <= 'H') {
        return Xwindow::Green;
    }
    if (c == 'I' ) {
        return Xwindow::Red;
    }
    if (c == 'J') {
        return Xwindow::Cyan;
    }
    if (c == 'K') {
        return Xwindow::White;
    }
    if (c == 'L') {
        return Xwindow::Yellow;
    }
    if (c >= 'M') {
        return Xwindow::Blue;
    }
    else {return Xwindow::Black;}
}


void GraphicalObserver::notify() {
    cout << "Printing Graphics..." << endl;

    // Constants for layout
    const int cellSize = 20;        // Size of each grid cell in pixels
    const int boundaryThickness = 5; // Thickness of the black boundary

    int gridWidth = max_col * cellSize;
    int gridHeight = max_row * cellSize;

    // Draw thick black boundaries
    window->fillRectangle(0, 0, gridWidth + 2 * boundaryThickness, boundaryThickness, Xwindow::Black); // Top boundary
    window->fillRectangle(0, 0, boundaryThickness, gridHeight + 2 * boundaryThickness, Xwindow::Black); // Left boundary
    window->fillRectangle(gridWidth + boundaryThickness, 0, boundaryThickness, gridHeight + 2 * boundaryThickness, Xwindow::Black); // Right boundary
    window->fillRectangle(0, gridHeight + boundaryThickness, gridWidth + 2 * boundaryThickness, boundaryThickness, Xwindow::Black); // Bottom boundary

    // Draw the grid cells and their content
    for (int row = 0; row < max_row; ++row) {
        for (int col = 0; col < max_col; ++col) {
            Position pos = {row, col};
            const Cell& cell = grid.at(pos);

            int cellX = col * cellSize + boundaryThickness;
            int cellY = row * cellSize + boundaryThickness;

            if (cell.link) {
                int color = convertCharacterToColor(cell.link->get_name());
                window->fillRectangle(cellX, cellY, cellSize, cellSize, color);
            } else if (cell.is_server_port) {
                int color = convertCharacterToColor('I');
                window->fillRectangle(cellX, cellY, cellSize, cellSize, color);
            } else if (cell.is_fire_wall) {
                if (cell.get_FW_owner() == 1) {
                    int color = convertCharacterToColor('L');
                    window->fillRectangle(cellX, cellY, cellSize, cellSize, color);
                } else if (cell.get_FW_owner() == 2) {
                    int color = convertCharacterToColor('J');
                    window->fillRectangle(cellX, cellY, cellSize, cellSize, color);
                } else {
                    int color = convertCharacterToColor('K');
                    window->fillRectangle(cellX, cellY, cellSize, cellSize, color);
                }
            } else {
                int color = convertCharacterToColor('K');
                window->fillRectangle(cellX, cellY, cellSize, cellSize, color);
            }
        }
    }
    cout << endl;
    cout << "Graphics updated!" << endl;
    cout << endl;
}
