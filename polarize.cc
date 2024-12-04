#include "polarize.h"
#include "link.h"
#include "player.h"
using namespace std;

Polarize::Polarize(): Ability{4, 'P', "Polarize"} {}
Polarize::~Polarize() {}

bool Polarize::activate(Player* player, Player* opponent, Board *theBoard, char link_name, int row, int col) {
    cout << "Polarize::activate called with link_name: " << link_name << endl;

    if (used) {
        cout << "Ability already used." << endl;
        return false;
    }

    Link* plink = nullptr;
    
    plink = player->find_link(link_name);
    cout << "Searching player's links..." << endl;
    if (! plink) {
        plink = opponent->find_link(link_name);
        cout << "Searching opponent's links..." << endl;
    }
    
    if (plink == nullptr) {
        cout << "The link " << link_name << " doesn't exist." << endl;
        return false;
    }

    cout << "Link found: " << link_name << " of type " << plink->get_type() << endl;

    if (plink->get_type() == 'D') {
        plink->set_type('V');
        used = true;
        cout << "Successfully polarized link " << link_name << " to type 'V'." << endl;
        return true;
    } else if (plink->get_type() == 'V') {
        plink->set_type('D');
        used = true;
        cout << "Successfully polarized link " << link_name << " to type 'D'." << endl;
        return true;
    } else {
        cout << "Wrong type of the link!" << endl;
        return false;
    }
}
