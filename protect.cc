#include "protect.h"
#include "link.h"
#include "player.h"
using namespace std;
Protect::Protect(): Ability{7, 'S', "Protect"} {}

Protect::~Protect() {}

bool Protect::activate( Player* player, Player* opponent, Board *theBoard, char link_name, int row, int col) {
    Link *plink = player->find_link(link_name);
    if (plink == nullptr) {
        cout << "Invalid link, please provide your opponent's link to Protect!" << endl;
        return false;
    }

    else {
        cout << "seting protection field in link " << link_name << "to be true" << endl;
        plink->set_protection();    // set protection field in link to be true
        used = true;
        cout << "Successfully applied Protect to link " << link_name << endl;
        return true;
    }
}

