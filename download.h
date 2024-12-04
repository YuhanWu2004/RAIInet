#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include "ability.h"
#include <iostream>
#include <string>

class Download: public Ability {

    public:
    Download();
    ~Download();
    bool activate( Player* player, Player* opponent, Board *theBoard, char link_name, int row, int col) override;

};

#endif
