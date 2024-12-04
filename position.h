#ifndef POSITION_H
#define POSITION_H
#include <tuple>
#include "link.h"


 struct Position { // Represents a position on the board
    int row;
    int col;

    public:
    int &get_row() {return row;}
    int &get_col() {return col;} 

    bool operator<(const Position &other) const {
        return std::tie(row, col) < std::tie(other.row, other.col);
    }

    };

#endif
