#include "player.h"
#include "ability.h"
#include "linkboost.h"
#include "firewall.h"
#include "download.h"
#include "polarize.h"
#include "scan.h"
#include "brutal.h"
#include "protect.h"
#include "trade.h"

using namespace std;

Player::Player(const string &placementFile, int num_abilities, int sequence)
    : num_abilities{num_abilities}, sequence{sequence}, downloaded_data{0}, downloaded_viruses{0} {
    ifstream file(placementFile);
    if (!file) {
        throw runtime_error("Unable to open placement file: " + placementFile);
    }

    char linkName = (sequence == 1) ? 'a' : 'A';

    string token;
    while (file >> token) {
        if (linkName > ((sequence == 1) ? 'h' : 'H')) {
            throw runtime_error("Too many links in placement file!");
        }

        if (token.size() != 2 || (token[0] != 'V' && token[0] != 'D') || !isdigit(token[1])) {
            throw runtime_error("Invalid link specification in placement file: " + token);
        }

        char type = token[0];
        int strength = token[1] - '0';

        links.push_back(make_unique<Link>(linkName++, type, strength));
    }

    if (links.size() != 8) {
        throw runtime_error("Invalid number of links in placement file!");
    }
}


bool Player::initializeAbilities(char new_ability) {
    // Add the new ability to the list_of_abilities based on the ability character
    try {
        switch (new_ability) {
            case 'L': // LinkBoost ability
                list_of_abilities.push_back(std::make_unique<LinkBoost>());
                return true;
            case 'F': // FireWall ability
                list_of_abilities.push_back(std::make_unique<FireWall>());
                return true;
            case 'D': // Download ability
                list_of_abilities.push_back(std::make_unique<Download>());
                return true;
            case 'S': // Scan ability
                list_of_abilities.push_back(std::make_unique<Scan>());
                return true;
            case 'P': // Polarize ability
                list_of_abilities.push_back(std::make_unique<Polarize>());
                return true;
            case 'B': // Polarize ability
                list_of_abilities.push_back(std::make_unique<Brutal>());
                return true;
            case 'C': // Polarize ability
                list_of_abilities.push_back(std::make_unique<Protect>());
                return true;
            case 'T': // Polarize ability
                list_of_abilities.push_back(std::make_unique<Trade>());
                return true;
            default:
                // Handle invalid ability characters
                cout << "Error in function Player::initializeAbilities: Invalid ability character '" 
                     << new_ability << "'" << endl;
                throw std::invalid_argument("Invalid ability character: " + std::string(1, new_ability));
        }
    } catch (const std::exception &e) {
        cout << "Exception caught during ability initialization: " << e.what() << endl;
        return false;
    }
}


int Player::get_id() const {return sequence;}

int Player::get_start_row() const {
    if (sequence == 1) return 0;
    if (sequence == 2) return 7;
    throw logic_error("Invalid player sequence");
}

int Player::get_downloaded_data() const {
    return downloaded_data;
}

int Player::get_downloaded_viruses() const {
    return downloaded_viruses;
}

int Player::get_num_abilities() const {
    return num_abilities;
}


std::map<char, int> &Player::get_abilities() {return abilities;}


const std::vector<std::unique_ptr<Ability>> &Player::get_list_of_abilities() const {return list_of_abilities;}

const vector<unique_ptr<Link>> &Player::get_links() const {
    return links;
}

const std::vector<std::string> &Player::get_downloaded_links() const {
    return downloaded_links;
}


void Player::display_player_full_info() const {
// Player's info
    // Player's name:
    cout << "Player " << sequence << ":" << endl;
    // Player's downloaded Links:
    cout << "Downloaded: " ;
    for (auto & s : downloaded_links) {
        cout << s << " ";
    }
    cout << endl;
    // Player's Abilities:
    cout << "Abilities: " << num_abilities << endl;

    // Player's own Links:
    // starts from 'a' or 'A'
    for (size_t i = 0; i < links.size(); ++i) {
        // Use a char to hold the starting character ('a' or 'A')
        char linkName = (sequence == 1 ? 'a' : 'A') + i;  // Add i to get the next character

        cout << linkName << ": " << links[i]->get_full_info() << " ";

        if (i % 4 == 3) cout << "\n"; // Wrap after every 4 links
    }
    cout << "\n";

}

void Player::display_player_info() const {
// Opponent's info

    // Opponent's name:
    cout << "Player " << sequence << ":" << endl;
    // Opponent's downloaded Links:
    cout << "Downloaded: " ;
    for (auto & s : downloaded_links) {
        cout << s << " ";
    }
    cout << endl;

    // Opponent's Abilities:
    cout << "Abilities: " << num_abilities << endl;

    // Opponent's own Links:
    // Starts from 'a' or 'A'
    for (size_t i = 0; i < links.size(); ++i) {
        // Use a char to hold the starting character ('a' or 'A')
        char linkName = (sequence == 1 ? 'a' : 'A') + i;  // Add i to get the next character

        cout << linkName << ": " << links[i]->get_info() << " ";

        if (i % 4 == 3) cout << "\n"; // Wrap after every 4 links
    }
    cout << endl;

}

void Player::display_abilities() const{
    int total = list_of_abilities.size();
    cout << "A total of " << total << " abilities" << endl;
    for (auto &p_abilities: list_of_abilities) {
        cout << p_abilities->getId() <<":" << p_abilities->getName() << " " << ! p_abilities->if_used() << endl;
    }

}


Link *Player::find_link(char link_name) const {
    for (const auto &link : links) {
        if (link->get_name() == link_name) {
            return link.get();
        }
    }
    return nullptr;
}


bool Player::addAbilities(char ability, int num) {
    bool result = true;
    for (int i = 0; i < num; ++i) {
        // Attempt to initialize the ability
        if (!initializeAbilities(ability)) {
            cout << "Failed to initialize ability: " << ability << " at iteration " << i + 1 << endl;
            result = false;
        }      
    }

    if (result) {
        // Update the player's ability map
        abilities[ability] += num;
        cout << "Successfully added " << num << " abilities of type '" << ability 
             << "'. Total now: " << abilities[ability] << endl;
        return true;
    } else {
        cout << "Error: One or more abilities could not be added for type '" << ability << "'" << endl;
        return false;
    }
}


void Player::addLink(unique_ptr<Link> new_link) {
    links.push_back(move(new_link));
}

bool Player::useAbility(char ability, char link_name, Player* player, Player* opponent, 
                        int row, int col, Board *board) {
        for (auto &p_ability : list_of_abilities) {
            if (p_ability->getChar() == ability && !p_ability->if_used()) {
                // Check the actual type
                // LinkBoost
                cout << "Activating ability of type: " << typeid(*p_ability).name() << endl;
                if (dynamic_cast<LinkBoost*>(p_ability.get())) {  // If using smart pointers
                    cout << "This ability is a LinkBoost." << endl;
                } 
                // FireWall
                else if (dynamic_cast<FireWall*>(p_ability.get())) {
                    cout << "This ability is FireWall." << endl;
                }
                // Download
                else if (dynamic_cast<Download*>(p_ability.get())) {
                    cout << "This ability is Download." << endl;
                }
                // Scan
                else if (dynamic_cast<Scan*>(p_ability.get())) {
                    cout << "This ability is Scan." << endl;
                }
                // Polarize
                else if (dynamic_cast<Polarize*>(p_ability.get())) {
                    cout << "This ability is Polarize." << endl;
                }
                // Brutal
                else if (dynamic_cast<Brutal*>(p_ability.get())) {
                    cout << "This ability is Brutal." << endl;
                }
                // Protect
                else if (dynamic_cast<Protect*>(p_ability.get())) {
                    cout << "This ability is Protect." << endl;
                }
                // Trade
                else if (dynamic_cast<Trade*>(p_ability.get())) {
                    cout << "This ability is Trade." << endl;
                }
                // Other
                else {
                    cout << "This ability is of other type!" << endl;
                }
                if (p_ability->activate(player, opponent, board, link_name, row ,col)) {
                    cout << "Ability successfully used!" << endl;
                    abilities[ability]--;
                    num_abilities--;
                    return true;
                }
                cout << "Ability activation failed" << endl;
                return false;
            }
        }






    cout << "Either the ability is no longer available or not found" << endl;
    return false;
}




bool Player::download(const Link &link) {
    if (link.get_type() == 'V') {
        string s = std::string(1, link.get_type()) + std::to_string(link.get_strength());
        downloaded_links.emplace_back(s);
        downloaded_viruses++;
        return true;
    } else if (link.get_type() == 'D') {
        string s = std::string(1, link.get_type()) + std::to_string(link.get_strength());
        downloaded_links.emplace_back(s);
        downloaded_data++;
        return true;
    }
    return false;
}

bool Player::won() const {
    return downloaded_data >= 4;
}

bool Player::lost() const {
    return downloaded_viruses >= 4;
}

