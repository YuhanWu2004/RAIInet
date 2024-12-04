#ifndef FIREWALL_H
#define FIREWALL_H

#include "ability.h"
#include <iostream>
#include <string>
using namespace std;
class Player;
class Board;

class FireWall: public Ability {

    public:
    FireWall();
    ~FireWall();
    bool activate(Player* player, Player* opponent, Board *theBoard, char link_name, int row, int col) override;

};

#endif
