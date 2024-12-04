#include "cell.h"

Cell::Cell(Link *l, bool isp, int SP_owner): 
link{l}, is_server_port{isp}, SP_owner{SP_owner}, is_fire_wall{false}, FW_owner{0} {}

bool Cell::get_FireWall() const {return is_fire_wall;}
int Cell::get_FW_owner() const {return FW_owner;}
int Cell::get_SP_owner() const {return SP_owner;}

bool Cell::setFireWall() {
    if (is_fire_wall) {
        return false;
    }
    else 
    {
        is_fire_wall = true;
        return true;
    }
}

bool Cell::setFW_owner(int n) {
    FW_owner = n;

    return true;
}
