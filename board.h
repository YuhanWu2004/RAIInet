#ifndef BOARD_H
#define BOARD_H

#include "subject.h"
#include "cell.h"
#include "position.h"
#include "player.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <map>
#include <memory>

class Board: public Subject {
    // Board size
    int max_row;
    int max_col;

    // Number of players
    int num_player;

    // Board grid mapping positions to Cells
    std::map<Position, Cell> grid;

    // Players participating in the game
    std::vector<Player *> players; // Raw pointers since Board doesn't manage Player memory

    // Helper functions
    Position find_link_position(Link *l) const; // Finds the position of a specific link
    bool battle(Position c1, Position c2, Player *p1, Player *p2); // Handles a battle between two links
    bool link_make_move(Player *player, Player *opponent, Link *link, const std::string &dir, Position pos); // Executes a link's move

public:

    // Constructor and Destructor
    Board(int mr, int mc, int np); // Initialize the board with given dimensions and player count
    ~Board(); 
    
    // Player Management
    void addPlayer(Player *new_player); // Adds a player to the board
    Player *getPlayer(int index) const; // Retrieves a player by index

    // Board Initialization
    void initialize_grid(Player &player1, Player &player2); // Set up the grid with initial positions

    // Link Management
    bool move(Player *player, Player * opponent, char link_name, const std::string &dir); // Moves a link on the board and updates its position
    Link *get_link_at(Position p); // Retrieves the Link at a specific position

    // Grid
    std::map<Position, Cell> &getGrid();  // Retirives the grid

    // Cell
    Cell &getCell(Position p);
    const Cell &retriveCell(Position p) const;

    // Getters
    int getRowSize() const;
    int getColSize() const;
    char getState( int row, int col ) const override;

    // Display
    void display_board(Player *current_player, Player *opponent) const;   // Outputs the board to the console
   
    // Game flow
    bool GameOver() const;        // Checks if the game has ended
};

#endif
