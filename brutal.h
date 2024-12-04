#ifndef BRUTAL_H
#define BRUTAL_H

#include "ability.h"
#include <iostream>
#include <string>

class Brutal: public Ability {

    public:
    Brutal();
    ~Brutal();
    bool activate(Player* player, Player* opponent, Board *theBoard, char link_name, int row, int col) override;

};
#endif

