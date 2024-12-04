#ifndef _TEXTOBSERVER_H_
#define _TEXTOBSERVER_H_

#include <iostream>

#include "board.h"
#include "observer.h"

class TextObserver : public Observer {
    Board *myBoard;
    Player *current_player;
    Player *opponent;
    std::map<Position, Cell> &grid;
    int max_row, max_col;

public:
    TextObserver(Board *myBoard, Player *current_player, Player *opponent, std::map<Position, Cell> &grid,
    int max_row, int max_col);
    Player *getPlayer() const override;
    void notify() override;
    ~TextObserver() override;
};

#endif
