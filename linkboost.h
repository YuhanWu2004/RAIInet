#ifndef LINKBOOST_H
#define LINKBOOST_H

#include "ability.h"

#include <iostream>
#include <string>
using namespace std;
class Player;

class LinkBoost: public Ability {

    public:
    LinkBoost();
    ~LinkBoost();
    bool activate(Player* player, Player* opponent, Board *theBoard, char link_name, int row, int col) override;

};

#endif

