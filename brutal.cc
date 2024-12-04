#include "brutal.h"
#include "link.h"
#include "player.h"
using namespace std;
Brutal::Brutal(): Ability{6, 'B', "Brutal"} {}

Brutal::~Brutal() {}
// This ability can be used on user’s own links to make sure the link wins any battle.
bool Brutal::activate( Player* player, Player* opponent, Board *theBoard, char link_name, int row, int col) {
    Link *plink = player->find_link(link_name);
    if (plink == nullptr) {
        cout << "Invalid link, please provide your opponent's link to Brutal!" << endl;
        return false;
    }

    else {
        cout << "Setting brutal on " << link_name << endl;
        plink->set_brutal();    // sets the brutal field in link to be true
        used = true;
        cout << "Successfully applied Brutal to link " << link_name << endl;
        return true;
    }
}

