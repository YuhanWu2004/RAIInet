#include "download.h"
#include "link.h"
#include "player.h"
using namespace std;
Download::Download(): Ability{3,'D', "Download"} {}

Download::~Download() {}

bool Download::activate(Player *player, Player* opponent, Board *theBoard, char link_name, int row, int col) {
    Link* plink = opponent->find_link(link_name);

    if (plink == nullptr) {
        cout << "Invalid link, please enter an opponent's link!" << endl;
        cout << "Player:" << player->get_id() << endl;
        return false;
    }
    else {
        if (plink->is_protected() ) {
            cout << "This link is protected, cannot be Downloaded!" << endl;
            return false;
        }
        else{
        cout << "downloading the link " <<  link_name << endl;
        // downloads the link
        player->download(*plink);
        // set the link downloaded
        plink->set_downloaded(true);
        used = true;
        cout << "Successfully downloaded link " << link_name << endl;
        return true;}
    }
}

