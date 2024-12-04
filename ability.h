#ifndef ABILITY_H
#define ABILITY_H

#include <iostream>
#include <string>
#include <memory>

using namespace std;

/* 
Abilities:
- L: Link Boost
- F: Firewall
- D: Download
- P: Polarize
- S: Scan
- B: Brutal
- P: Protect
- T: Trade
*/
class Player;
class Board;

class Ability {
    int id;      
    char c;  
    string abilityName;
protected:
    bool used;
public:
    Ability(int id, char c, const string& name, bool used = false);
    virtual ~Ability() = 0;  // Pure virtual destructor
    virtual bool activate( Player* player, Player* opponent, Board * theBoard = nullptr, char link_name = '0', int row = -1, int col = -1) = 0;
    int getId() const;
    bool if_used() const;
    char getChar() const;
    string getName() const;
};


#endif
