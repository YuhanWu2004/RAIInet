#include "trade.h"
#include "link.h"
#include "player.h"
using namespace std;
Trade::Trade(): Ability{8, 'T', "Trade"} {}

Trade::~Trade() {}

bool Trade::activate( Player* player, Player* opponent, Board *theBoard, char link_name, int row, int col) {
    // make sure the link_name is player's link
    Link * plink1 = nullptr;
    plink1 = player->find_link(link_name);
    if (plink1 == nullptr) {
        cout << "Invalid link, please enter one of your own links!" << endl;
        return false;
    }
    if (plink1->is_downloaded()) {
        cout << "Invalid link, this link "  << link_name << " has already been downloaded!" << endl;
        return false;
    }

    char new_link_name = link_name;
    if (link_name >= 'a' && link_name <= 'h') {
        new_link_name = link_name - 'a' + 'A';
        cout << "The corresponding link to trade with your opponent is: " << new_link_name << endl;

    }
    if (link_name >= 'A' && link_name <= 'H') {
        new_link_name = link_name - 'A' + 'a';
        cout << "The corresponding link to trade with your opponent is: " << new_link_name << endl;
    }

    Link *plink2 = opponent->find_link(new_link_name);
    if ( plink2 == nullptr) {
        cout << "There's no such link" << new_link_name << " belonging to player " << opponent->get_id() << endl;
        return false;
    }

    cout << "Player " << plink2->get_player() <<  plink2->get_name() << "is_downloaded? " << plink2->is_downloaded() << endl;
    if (plink2->is_downloaded()) {
        cout << "Invalid link, your opponent's link "  << new_link_name << " has already been downloaded!" << endl;
        return false;
    }

    else {
        Link tmp(*plink2);
        *plink2 = *plink1;
        plink2->set_name(new_link_name);
        *plink1 = tmp;
        plink1->set_name(link_name);
        cout << "Successfully applied Trade to link " << link_name << endl;
        cout << "Player" << player->get_id() << "now has link: " << player->find_link(link_name)->get_full_info() << endl;
        cout << "Player" << opponent->get_id() << "now has link: " << opponent->find_link(new_link_name)->get_full_info() << endl;
        return true;
    }
}

