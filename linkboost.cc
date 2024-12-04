#include "linkboost.h"
#include "player.h"

LinkBoost::LinkBoost(): Ability{1, 'L', "LinkBoost"} {
    cout << "LinkBoost constructed." << endl;
}

LinkBoost::~LinkBoost() {}

bool LinkBoost::activate(Player* player, Player* opponent, Board* theBoard, char link_name, int row, int col) {
    cout << "LinkBoost::activate called with link_name: " << link_name << endl;
    // Find the link by name
    Link* link = player->find_link(link_name);
    if (!link) {
        cout << "Invalid link name '" << link_name << "'. Ability not activated." << endl;
        return false;
    }

    // Check if the link is already boosted
    if (link->is_linkboost()) {
        cout << "Link '" << link_name << "' has already been boosted. Ability not activated." << endl;
        return false;
    }

    // Boost the link
    link->set_linkboost();
    used = true; // Mark the ability as used
    cout << "Link '" << link_name << "' has been boosted successfully." << endl;
    return true; // Successful activation
}
