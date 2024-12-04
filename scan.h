#ifndef SCAN_H
#define SCAN_H

#include "ability.h"
#include <iostream>
#include <string>

class Scan: public Ability {

    public:
    Scan();
    ~Scan();
    bool activate(Player* player, Player* opponent, Board *theBoard, char link_name, int row, int col) override;

};

#endif

