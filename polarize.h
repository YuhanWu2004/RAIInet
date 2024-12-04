#ifndef POLARIZE_H
#define POLARIZE_H

#include "ability.h"
#include <iostream>
#include <string>

class Polarize: public Ability {

    public:
    Polarize();
    ~Polarize();
    bool activate(Player* player, Player* opponent, Board *theBoard, char link_name, int row, int col) override;

};

#endif
