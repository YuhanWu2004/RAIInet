#ifndef _GRAPHICALOBSERVER_H_
#define _GRAPHICALOBSERVER_H_

#include <iostream>

#include "board.h"
#include "window.h"
#include "observer.h"

// class Board;

class GraphicalObserver : public Observer {
    Board * myBoard;
    Player *current_player;
    Player *opponent;
    std::map<Position, Cell> &grid;
    Xwindow * window;
    int max_row, max_col;

    int convertCharacterToColor(char c);
private:
    std::string previousPlayer1Info;
    std::string previousPlayer2Info;


public:
    GraphicalObserver(Board *myBoard, Player *current_player, Player *opponent, std::map<Position, Cell> &grid,
     Xwindow *window, int max_row, int max_col);
    void displayPlayerInfoGraphically(const Player *player, int startX, int startY);
    void updatePlayerInfoGraphically(Player *player, int startX, int startY, std::string &previousInfo);
    Player *getPlayer() const override;
    void notify() override;
    ~GraphicalObserver() override;
};

#endif
