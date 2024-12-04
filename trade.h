#ifndef TRADE_H
#define TRADE_H

#include "ability.h"
#include <iostream>
#include <string>

class Trade: public Ability {

    public:
    Trade();
    ~Trade();
    bool activate(Player* player, Player* opponent, Board *theBoard, char link_name, int row, int col) override;

};

#endif

