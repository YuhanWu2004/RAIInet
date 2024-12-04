#include "scan.h"
#include "link.h"
#include "player.h"
using namespace std;
Scan::Scan(): Ability{5, 'S', "Scan"} {}

Scan::~Scan() {}

bool Scan::activate( Player* player, Player* opponent, Board *theBoard, char link_name, int row, int col) {
    Link *plink = opponent->find_link(link_name);
    if (plink == nullptr) {
        cout << "Invalid link, please provide your opponent's link to Scan!" << endl;
        return false;
    }

    else {
        if (plink->is_protected() ) {
            cout << "This link is protected, cannot be scanned!" << endl;
            return false;
        }
        else {
        plink->set_revealed(true);
        used = true;
        cout << "Successfully applied scan to link " << link_name << endl;
        return true;}
    }
}

