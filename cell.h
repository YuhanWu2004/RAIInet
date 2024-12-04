#ifndef CELL_H
#define CELL_H

#include "link.h"


 struct Cell { // Represents a single cell on the board
        Link *link;         // Pointer to a Link (managed by Player)
        bool is_server_port; // True if this cell is a server port
        int SP_owner;
        bool is_fire_wall;
        int FW_owner;
        // Constructor with default values
        public:
        Cell(Link *l = nullptr, bool isp = false, int SP_owner = 0);
        bool get_FireWall() const;
        int get_FW_owner() const;
        int get_SP_owner() const;

        bool setFireWall();
        bool setFW_owner(int n);
    };

#endif
