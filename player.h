#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>
#include <memory> // For unique_ptr
#include <string>


#include "link.h"
#include "ability.h"


class Ability;

class Player {
    std::vector<std::unique_ptr<Link>> links; // Smart pointer for automatic memory management
    std::vector<std::unique_ptr<Ability>> list_of_abilities;
    std::map<char, int> abilities;           // Tracks remaining uses of abilities
    
    int num_abilities;
    int sequence;                            // 1 or 2 to identify the player
    int downloaded_data;                     // Tracks the number of downloaded data links
    int downloaded_viruses;                  // Tracks the number of downloaded virus links
    std::vector<std::string> downloaded_links; // Holds names of all downloaded links


public:
    // Constructor to initialize the player with placement file and abilities
    Player(const std::string &placementFile, int num_abilities, int sequence);

    bool initializeAbilities(char new_ability);

    // Destructor automatically handles memory management with unique_ptr
    ~Player() = default;

    // Getters
    int get_id() const;
    int get_start_row() const; // Returns the starting row for the player
    int get_downloaded_data() const;
    int get_downloaded_viruses() const;
    int get_num_abilities() const;  
    std::map<char, int> &get_abilities();    // get abilities
    const std::vector<std::unique_ptr<Ability>> &get_list_of_abilities() const;
    const std::vector<std::unique_ptr<Link>> &get_links() const;
    const std::vector<std::string> &get_downloaded_links() const;

    // Display full info
    void display_player_full_info() const;

    // Display info
    void display_player_info() const;

    void display_abilities() const;

    // Finds the link by its name
    Link *find_link(char link_name) const;

    // Adds a link to the player's list
    void addLink(std::unique_ptr<Link> new_link);

    // Add abilities
    bool addAbilities(char ability, int num);

    // Attempts to use an ability
    bool useAbility(char ability, char link_name, Player* player, Player* opponent, int row = -1, int col = -1, Board *board = nullptr);

    // Downloads a link (increments downloaded data or virus count)
    bool download(const Link &link);

    // Determines if the player has won or lost
    bool won() const;
    bool lost() const;
};

#endif
