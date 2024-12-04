#ifndef PROTECT_H
#define PROTECT_H

#include "ability.h"
#include <iostream>
#include <string>

class Protect: public Ability {

    public:
    Protect();
    ~Protect();
    bool activate(Player* player, Player* opponent, Board *theBoard, char link_name, int row, int col) override;

};

#endif
