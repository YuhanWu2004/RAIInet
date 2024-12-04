#include "firewall.h"
#include "board.h"

FireWall::FireWall(): Ability{2, 'F', "FireWall"} {}


FireWall::~FireWall() {}

bool FireWall::activate(Player* player, Player* opponent, Board *theBoard, char link_name, int row, int col) {
    if (row< 0 || row > theBoard->getRowSize() ||
    col < 0 || col > theBoard->getColSize()) {
        cout << "Invalid coordinates, enter again: "<< endl;
        return false;
    }
    else {
        Position p{row, col};
        Cell &theCell = theBoard->getCell(p);
        if (theCell.get_FireWall()) {
            cout << "Link " << col << " has already been set to firewall! " << endl;
            return false;
        }
        else {
            // Set the firewall field in the Cell to be true and set the owner of firewall
            theCell.setFireWall();
            theCell.setFW_owner(player->get_id());
            used = true;
            cout << "Cell (" << row << ", " << col <<")" << " is successfully set to firewall!" << theCell.get_FireWall() <<  endl; 
            return true;
        }

    }
}

